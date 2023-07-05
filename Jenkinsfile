pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                echo 'Build docs to html files'
                sh "git clean -dfx"
                sh "cmake -G Ninja -DCMAKE_BUILD_TYPE=release -B build"
                sh "cmake --build build"
                sh "ctest --test-dir build"
            }
        }
    }
}

