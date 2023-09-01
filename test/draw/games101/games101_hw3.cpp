#include "gpu_execuator.hpp"
#include "games101_common.hpp"
#include "games101_config.hpp"
#include "OBJ_Loader.h"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
#include <iostream>

struct triangle {
    Eigen::Vector4f v[3];
    Eigen::Vector2f tex_coords[3];
    Eigen::Vector3f normal[3];
};

struct box_info {
    uint32_t box_l;
    uint32_t box_b;
    uint32_t box_width;
};

struct tex_info {
    uint8_t *tex_buffer;
    uint32_t tex_width;
    uint32_t tex_height;
};

TEST_F(GPUExecuator, games101_hw3) {
    // 1. Data preparation
    // 1.1 Matrices
    float angle = 140.0;
    Eigen::Vector3f eye_pos = {0,0,10};

    Eigen::Matrix4f model = get_model_matrix_hw3(angle);
    Eigen::Matrix4f view = get_view_matrix(eye_pos);
    Eigen::Matrix4f projection = get_projection_matrix(45, 1, 0.1, 50);


    std::cout<<"model: "<<model<<std::endl;
    std::cout<<"view: "<<view<<std::endl;
    std::cout<<"projection: "<<projection<<std::endl;

    // 1.2 Triangles
    std::vector<struct triangle *> TriangleList;
    objl::Loader Loader;

    std::string obj_path = PROJECT_TEST_DRAW_PATH;
    obj_path += "/games101/models/spot/";

    std::cout<<"obj_path: "<<obj_path<<std::endl;

    // Load .obj File
    bool loadout = Loader.LoadFile(obj_path + "spot_triangulated_good.obj");

    printf("loadout %d\n", loadout);
    
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
                // std::cout<<"t->v[j]: "<<t->v[j]<<std::endl;

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

    printf("triangle_num: %d\n", triangle_num);
    printf("vertex_num: %d\n", vertex_num);


    Eigen::Vector4f *vertex_positions = (Eigen::Vector4f *) malloc(vertex_num * sizeof(Eigen::Vector4f));

    for (int i = 0; i < triangle_num; i ++) {
        vertex_positions[i * 3 + 0] = TriangleList[i]->v[0];
        vertex_positions[i * 3 + 1] = TriangleList[i]->v[1];
        vertex_positions[i * 3 + 2] = TriangleList[i]->v[2];
    }

    // print the first 30 vertices
    for (int i = 0; i < 30; i ++) {
        printf("Before vs\n");
        std::cout<<vertex_positions[i]<<std::endl;
    }

    // 1.3 Texture
    auto texture_path = "spot_texture.png";
    std::string tex_name = obj_path + texture_path;

    // Read texture data
    cv::Mat image_data = cv::imread(tex_name);
    cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);

    uint32_t tex_width = image_data.cols;
    uint32_t tex_height = image_data.rows;

    uint8_t *tex_buffer = (uint8_t *) calloc(tex_width * tex_height * 4, sizeof(uint8_t));

    // Copy tex data to tex buffer
    for (uint32_t x = 0; x < tex_width; x++) {
        for (uint32_t y = 0; y < tex_height; y++) {
            auto color = image_data.at<cv::Vec3b>(y, x);

            tex_buffer[(y * tex_width + x) * 4 + 0] = (uint8_t)color[0];
            tex_buffer[(y * tex_width + x) * 4 + 1] = (uint8_t)color[1];
            tex_buffer[(y * tex_width + x) * 4 + 2] = (uint8_t)color[2];
            tex_buffer[(y * tex_width + x) * 4 + 3] = 255;
        }
    }

    std::cout<<tex_width<<" --> tex_width\n";
    std::cout<<tex_height<<" --> tex_height\n";

    std::string fpath = "texture.ppm";
    FILE *wf = fopen(fpath.c_str(), "w");
    fprintf(wf, "P3\n");
    fprintf(wf, "1024 1024\n");
    fprintf(wf, "255\n");
    for (uint32_t i=0; i<tex_height; i++) {
        for (uint32_t j=0; j<tex_width; j++) {
            uint32_t index = i * tex_width + j;
            uint8_t r = tex_buffer[index * 4 + 0];
            uint8_t g = tex_buffer[index * 4 + 1];
            uint8_t b = tex_buffer[index * 4 + 2];
            // uint8_t a = testfb[index + 0];
            fprintf(wf, "%d %d %d\n", r, g, b);
        }
    }

    fclose(wf);


// --------------------



    // 2. Vertex shader
    Eigen::Vector4f *vs_out_positions = (Eigen::Vector4f *) malloc(vertex_num * sizeof(Eigen::Vector4f));

    // Run 910 vertices
    LoadELF("games101", "games101_hw3_vertex_shader");
    PushParam(0); // tid
    PushParam((uint64_t)vertex_positions);
    PushParam((uint64_t)vs_out_positions);
    PushParam((uint64_t)(&model));
    PushParam((uint64_t)(&view));
    PushParam((uint64_t)(&projection));
    run1d(910);

    // print the first 30 vertices
    for (int i = 0; i < 30; i ++) {
        printf("After vs\n");
        std::cout<<vs_out_positions[i]<<std::endl;
    }



// --------------------



    // 3. Rasterization
    uint8_t *color_buffer = (uint8_t *) calloc(WIDTH * HEIGHT * 4, sizeof(uint8_t));
    float *depth_buffer = (float *) calloc(WIDTH * HEIGHT, sizeof(float));

    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        depth_buffer[i] = -1.0f;
    }

    // Iterate over triangles
    struct tex_info tex;
    tex.tex_buffer = tex_buffer;
    tex.tex_width = tex_width;
    tex.tex_height = tex_height;

    std::cout<<tex_width<<" --> tex_width\n";
    std::cout<<tex_height<<" --> tex_height\n";

    // Run 300 triangles    
    for (int i = 0; i < 300; i++) {
        // printf("Triangle %d\n", i);

        Eigen::Vector4f v0 = vs_out_positions[i * 3 + 0];
        Eigen::Vector4f v1 = vs_out_positions[i * 3 + 1];
        Eigen::Vector4f v2 = vs_out_positions[i * 3 + 2];

        struct triangle t;
        t.v[0] = v0;
        t.v[1] = v1;
        t.v[2] = v2;

        Eigen::Vector3f triangle_x(v0.x(), v1.x(), v2.x());
        Eigen::Vector3f triangle_y(v0.y(), v1.y(), v2.y());

        // Bounding box
        uint32_t box_l = (uint32_t)triangle_x.minCoeff();
        uint32_t box_r = (uint32_t)triangle_x.maxCoeff() + 1;
        uint32_t box_b = (uint32_t)triangle_y.minCoeff();
        uint32_t box_t = (uint32_t)triangle_y.maxCoeff() + 1;

        uint32_t box_width = box_r - box_l;
        uint32_t box_height = box_t - box_b;

        /*
        printf("box_l: %u\n", box_l);
        printf("box_r: %u\n", box_r);
        printf("box_b: %u\n", box_b);
        printf("box_t: %u\n", box_t);
        printf("box_width: %u\n", box_width);
        printf("box_height: %u\n", box_height);
        */

        struct box_info box = {box_l, box_b, box_width};
        
        // Iterate over bounding box
        LoadELF("games101", "games101_hw3_rasterization");
        PushParam(0); // tid
        PushParam((uint64_t)(&t));
        PushParam((uint64_t)color_buffer);
        PushParam((uint64_t)depth_buffer);
        PushParam((uint64_t)(&tex));        
        PushParam((uint64_t)(&box));
        run1d(box_width * box_height);        
    }



// --------------------



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

    WritePPM("games101_hw3", WIDTH, HEIGHT, image);


}
