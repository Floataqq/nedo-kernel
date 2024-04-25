@clean:
  rm -rf build
  mkdir build

build:
  exec scripts/build_cpp.sh
  exec scripts/build_asm.sh
  ld -n -o build/kernel.bin -T src/linker.ld build/*.o
  cp build/kernel.bin isofiles/boot

iso: build
  grub-mkrescue -o build/os.iso isofiles

run: iso
  qemu-system-x86_64 -cdrom build/os.iso

