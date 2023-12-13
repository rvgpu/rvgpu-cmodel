#! /bin/bash

function build()
{
    mkdir -p ${install_dir}

    cmake \
        -S /source/ \
        -B ${workspace}/build \
        -G Ninja \
        -DCMAKE_INSTALL_PREFIX=${install_dir} \
        -DBUILD_PACKAGE=on \
        -DCMAKE_BUILD_TYPE=release

    if [ $? -ne 0 ]; then
        echo "cmake error and exit"
        exit -1
    fi

    cmake --build ${workspace}/build
    if [ $? -ne 0 ]; then
        echo "cmake build error and exit"
        exit -1
    fi

    ctest --test-dir ${workspace}/build
    if [ $? -ne 0 ]; then
        echo "cmake test error and exit"
        exit -1
    fi

    cmake --install ${workspace}/build
    if [ $? -ne 0 ]; then
        echo "install error"
        exit -1
    fi
}

function package_deb()
{
    pushd ${workspace}
        mkdir -p debian
        rsync -rat /source/.ci/debian-package/* ${workspace}/debian/
        dpkg -b debian/ /source/rvgpu-csim_0.2.2_amd64.deb
    popd
}

workspace=/source/cibuild/
install_dir=${workspace}/debian/usr/local/rvgpu
mkdir -p ${install_dir}
# Build RVGPU CSim
build

# Package
package_deb

# clean
rm -rf ${workspace}
