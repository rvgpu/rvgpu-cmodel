#include "gpu_execuator.hpp"
#include "games101_common.hpp"
#include "games101_config.hpp"
#include "OBJ_Loader.h"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>

#include "data/games101_hw3_vertex_shader.hpp"
#include "data/games101_hw3_displacement_shader.hpp"

TEST_F(GPUExecuator, games101_hw3_displacement_shader) {
    // 1. Data preparation
    // 1.1 Matrices
    float angle = 140.0;
    Eigen::Vector3f eye_pos = {0,0,10};

    Eigen::Matrix4f model = get_model_matrix_hw3(angle);
    Eigen::Matrix4f view = get_view_matrix(eye_pos);
    Eigen::Matrix4f projection = get_projection_matrix(45, 1, 0.1, 50);

    // 1.2 Triangles
    std::vector<struct triangle *> TriangleList;
    objl::Loader Loader;

    std::string obj_path = PROJECT_TEST_DRAW_PATH;
    obj_path += "/games101/models/spot/";

    // Load .obj File
    bool loadout = Loader.LoadFile(obj_path + "spot_triangulated_good.obj");
    
    for(auto mesh : Loader.LoadedMeshes)
    {
        for(unsigned int i = 0; i < mesh.Vertices.size(); i += 3)
        {
            struct triangle *t = (struct triangle *) malloc(sizeof(struct triangle));

            for(int j = 0; j < 3; j++)
            {
                t->v[j] = Eigen::Vector4f(
                    mesh.Vertices[i+j].Position.X,
                    mesh.Vertices[i+j].Position.Y,
                    mesh.Vertices[i+j].Position.Z,
                    1.0);

                t->normal[j] = Eigen::Vector3f(
                    mesh.Vertices[i+j].Normal.X,
                    mesh.Vertices[i+j].Normal.Y,
                    mesh.Vertices[i+j].Normal.Z);

                t->tex_coords[j] = Eigen::Vector2f(
                    mesh.Vertices[i+j].TextureCoordinate.X,
                    mesh.Vertices[i+j].TextureCoordinate.Y);
            }

            TriangleList.push_back(t);
        }
    }

    int triangle_num = TriangleList.size();
    int vertex_num = triangle_num * 3;

    Eigen::Vector4f *vertex_positions = (Eigen::Vector4f *) malloc(vertex_num * sizeof(Eigen::Vector4f));

    for (int i = 0; i < triangle_num; i ++) {
        vertex_positions[i * 3 + 0] = TriangleList[i]->v[0];
        vertex_positions[i * 3 + 1] = TriangleList[i]->v[1];
        vertex_positions[i * 3 + 2] = TriangleList[i]->v[2];
    }

    // 1.3 Texture
    auto texture_path = "hmap.jpg";
    std::string tex_name = obj_path + texture_path;

    cv::Mat image_data = cv::imread(tex_name);
    cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);

    uint32_t tex_width = image_data.cols;
    uint32_t tex_height = image_data.rows;

    uint8_t *tex_buffer = (uint8_t *) calloc(tex_width * tex_height * 4, sizeof(uint8_t));

    for (uint32_t x = 0; x < tex_width; x++) {
        for (uint32_t y = 0; y < tex_height; y++) {
            auto color = image_data.at<cv::Vec3b>(y, x);

            tex_buffer[(y * tex_width + x) * 4 + 0] = (uint8_t)color[0];
            tex_buffer[(y * tex_width + x) * 4 + 1] = (uint8_t)color[1];
            tex_buffer[(y * tex_width + x) * 4 + 2] = (uint8_t)color[2];
            tex_buffer[(y * tex_width + x) * 4 + 3] = 255;
        }
    }

    // 2. Vertex shader
    Eigen::Vector4f *vs_out_positions = (Eigen::Vector4f *) malloc(vertex_num * sizeof(Eigen::Vector4f));

#if RUN_ON_GPU
    LoadELF("games101", "games101_hw3_vertex_shader");
    PushParam(0); // tid
    PushParam((uint64_t)vertex_positions);
    PushParam((uint64_t)vs_out_positions);
    PushParam((uint64_t)(&model));
    PushParam((uint64_t)(&view));
    PushParam((uint64_t)(&projection));
    run1d(vertex_num);
#else
    for (long tid = 0; tid < vertex_num; tid++) {
        vertex_shader(tid, vertex_positions, vs_out_positions, &model, &view, &projection);
    }
#endif

    // 3. Rasterization
    uint8_t *color_buffer = (uint8_t *) calloc(WIDTH * HEIGHT * 4, sizeof(uint8_t));
    float *depth_buffer = (float *) calloc(WIDTH * HEIGHT, sizeof(float));

    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        depth_buffer[i] = -1.0f;
    }

    struct tex_info tex;
    tex.tex_buffer = tex_buffer;
    tex.tex_width = tex_width;
    tex.tex_height = tex_height;

    Eigen::Matrix4f view_model = view * model;
    Eigen::Matrix4f inv_trans = view_model.inverse().transpose();

    // Iterate over triangles
    for (int i = 0; i < triangle_num; i++) {
        struct triangle t;

        Eigen::Vector4f viewspace_normal[3];
        Eigen::Vector4f viewspace_pos[3];

        for (int j = 0; j < 3; j++) {
            t.v[j] = vs_out_positions[i * 3 + j];
            t.color[j] = {148.0 / 255.0, 121.0 / 255.0, 92.0 / 255.0};
            t.tex_coords[j] = TriangleList[i]->tex_coords[j];

            viewspace_normal[j] << TriangleList[i]->normal[j], 0.0f;
            viewspace_normal[j] = inv_trans * viewspace_normal[j];
            t.normal[j] = viewspace_normal[j].head<3>();

            viewspace_pos[j] = view_model * TriangleList[i]->v[j];
        }

        Eigen::Vector3f triangle_x(t.v[0].x(), t.v[1].x(), t.v[2].x());
        Eigen::Vector3f triangle_y(t.v[0].y(), t.v[1].y(), t.v[2].y());

        // Bounding box
        uint32_t box_l = (uint32_t)triangle_x.minCoeff();
        uint32_t box_r = (uint32_t)triangle_x.maxCoeff() + 1;
        uint32_t box_b = (uint32_t)triangle_y.minCoeff();
        uint32_t box_t = (uint32_t)triangle_y.maxCoeff() + 1;

        uint32_t box_width = box_r - box_l;
        uint32_t box_height = box_t - box_b;

        struct box_info box = {box_l, box_b, box_width};

        // Iterate over bounding box
#if RUN_ON_GPU
        LoadELF("games101", "games101_hw3_displacement_shader");
        PushParam(0); // tid
        PushParam((uint64_t)(&t));
        PushParam((uint64_t)color_buffer);
        PushParam((uint64_t)depth_buffer);
        PushParam((uint64_t)(&tex));        
        PushParam((uint64_t)(&box));
        PushParam((uint64_t)viewspace_pos);
        run1d(box_width * box_height);
#else
        for (long tid = 0; tid < box_width * box_height; tid++) {
            displacement_shader(tid, &t, color_buffer, depth_buffer, &tex, &box, viewspace_pos);
        }
#endif
    }

    // 4. Write to image
    uint8_t *image = (uint8_t *) calloc(WIDTH * HEIGHT * 4, sizeof(uint8_t));

    uint32_t img_pid, cb_pid;

    for (uint32_t x = 0; x < WIDTH; x++) {
        for (uint32_t y = 0; y < HEIGHT; y++) {
            img_pid = y * WIDTH + x;
            cb_pid = (HEIGHT - 1 - y) * WIDTH + x;

            image[img_pid * 4 + 0] = color_buffer[cb_pid * 4 + 0];
            image[img_pid * 4 + 1] = color_buffer[cb_pid * 4 + 1];
            image[img_pid * 4 + 2] = color_buffer[cb_pid * 4 + 2];
            image[img_pid * 4 + 3] = color_buffer[cb_pid * 4 + 3];
        }
    }

    WritePPM("games101_hw3_displacement_shader", WIDTH, HEIGHT, image);
}
