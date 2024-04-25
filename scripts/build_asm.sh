for i in $(ls src/*.asm); do
  nasm -f elf64 $i -o build/$(basename $i.o)
done
