# ~/git/rvgpu/install/bin/clang -emit-llvm -c test.c -S -o test.ll --target="riscv64-unknown-linux-gnu"
# ~/git/rvgpu/install/bin/llc test.ll -mcpu="rvgpu" -O3 --filetype=obj
~/git/rvgpu/install/bin/clang -c $1 -o test --target="riscv64-unknown-linux-gnu" -mcpu="rvgpu"
~/git/rvgpu/install/bin/llvm-objdump -d test
