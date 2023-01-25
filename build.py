import os


def main():
    os.chdir("src/")
    os.system("make")
    os.chdir("..")
    if not os.path.exists('iso_dir/'):
        os.makedirs('iso_dir/')
    os.system("dd if=/dev/zero of=fat.img bs=1k count=1440")
    os.system("mformat -i fat.img -f 1440 ::")
    os.system("mmd -i fat.img ::/EFI")
    os.system("mmd -i fat.img ::/EFI/BOOT")
    os.system("mmd -i fat.img ::/files")
    os.system("mcopy -i fat.img BOOTX64.EFI ::/EFI/BOOT")
    os.system("mcopy -i fat.img iso_dir ::/files")
    os.system("xorriso -as mkisofs -o CumOS.iso -iso-level 3 -V UEFI iso_dir -append_partition 2 0xef fat.img -e --interval:appended_partition_2:all:: -no-emul-boot")



if __name__ == '__main__':
    main()