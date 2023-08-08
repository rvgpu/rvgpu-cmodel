# ~/git/rvgpu/install/bin/clang -emit-llvm -c test.c -S -o test.ll --target="riscv64-unknown-linux-gnu"
# ~/git/rvgpu/install/bin/llc test.ll -mcpu="rvgpu" -O3 --filetype=obj

fname=`echo "${1%.*}"`

# ~/git/rvgpu/install/bin/clang -emit-llvm -c $1 -S -o test.ll -target riscv64 -mcpu="rvgpu" -fno-pic -fno-omit-frame-pointer -mno-save-restore -fno-common -mcmodel=medany
# ~/git/rvgpu/install/bin/clang -emit-llvm -c $1 -S -o test.ll -target riscv64 -mcpu="rvgpu" -mcmodel=medlow -mno-relax
# ~/git/rvgpu/install/bin/llc test.ll -mcpu="rvgpu" -O3 
# ~/git/rvgpu/install/bin/llvm-objdump -d test.o > ${fname}.vs

echo "### Clang"
~/git/rvgpu/install/bin/clang -c $1 -target riscv64 -mcpu="rvgpu" -v -mcmodel=medany

echo "### ld.lld"
~/git/rvgpu/install/bin/ld.lld $fname.o -o ${fname}  -egpumain

# echo "### llvm-objdump"
# ~/git/rvgpu/install/bin/llvm-objdump -D ${fname} > log

rm -f ${fname}.o
