#include "kernel.h"


/* public domain image loader - http://nothings.org/stb_image.h */
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void fuckup(int fuck) {
    printf("\nfuckup: %d", fuck);
    // Не бойтесь, тут тупо стопорим процессор командой hlt, чтобы он зря не грелся
    __asm__("cli");
    for(;;) {
        __asm__("hlt");
    }
}

/**
 * Classic Hello World example
 */
int main(int argc, char **argv) {
    (void)argc;
    (void)argv;

    efi_status_t status;
    efi_guid_t gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
    efi_gop_t *gop = NULL;
    FILE *f;
    long int size;

    /* load font */
    if((f = fopen("\\files\\iso_dir\\font.sfn", "r"))) {
        fseek(f, 0, SEEK_END);
        size = ftell(f);
        fseek(f, 0, SEEK_SET);
        font = (ssfn_font_t*)malloc(size + 1);
        if(!font) {
            fprintf(stderr, "unable to allocate memory\n");
            return 1;
        }
        fread(font, size, 1, f);
        fclose(f);
    } else {
        fprintf(stderr, "Unable to load font\n");
        return 0;
    }

    /* set video mode */
    status = BS->LocateProtocol(&gopGuid, NULL, (void**)&gop);
    if(!EFI_ERROR(status) && gop) {
        status = gop->SetMode(gop, 0);
        ST->ConOut->Reset(ST->ConOut, 0);
        ST->StdErr->Reset(ST->StdErr, 0);
        if(EFI_ERROR(status)) {
            fprintf(stderr, "unable to set video mode\n");
            return 0;
        }
        /* set up destination buffer */
        lfb = (unsigned char*)gop->Mode->FrameBufferBase;
        width = gop->Mode->Information->HorizontalResolution;
        height = gop->Mode->Information->VerticalResolution;
        pitch = sizeof(unsigned int) * gop->Mode->Information->PixelsPerScanLine;
    } else {
        fprintf(stderr, "unable to get graphics output protocol\n");
        return 0;
    }

    /* display multilingual text */
    printString(0, 0, "CumOS 0.1.0");
    printString(0, 0, "Приветствуем в CUM OS!");

    /* free resources exit */
    free(font);
    // Не бойтесь, тут тупо стопорим процессор командой hlt, чтобы он зря не грелся
    __asm__("cli");
    for(;;) {
        __asm__("hlt");
    }
    return 0;
}