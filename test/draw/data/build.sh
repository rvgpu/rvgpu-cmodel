# ~/git/rvgpu/install/bin/clang -emit-llvm -c test.c -S -o test.ll --target="riscv64-unknown-linux-gnu"
# ~/git/rvgpu/install/bin/llc test.ll -mcpu="rvgpu" -O3 --filetype=obj

fname=`echo "${1%.*}"`

~/git/rvgpu/install/bin/clang -emit-llvm -c $1 -S -o test.ll -target riscv64 -mcpu="rvgpu" -fno-pic -fno-omit-frame-pointer -mno-save-restore -fno-common -mcmodel=medany
~/git/rvgpu/install/bin/llc test.ll -mcpu="rvgpu" -O3 --filetype=obj
~/git/rvgpu/install/bin/llvm-objdump -d test.o > ${fname}.vs

rm -f test.o test.ll
