#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <gtk/gtk.h>

// use sdl lib
// use qt lib

void destroy(void) {
  gtk_main_quit();
}

void displayImage(struct buff input, int   argc, char** argv){
 GtkWidget* window;
  GtkWidget* image;

  gtk_init (&argc, &argv);

    //input.img
const int Width = input.width, Height = input.height;
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data (input.imageName, GDK_COLORSPACE_RGB,
      FALSE, 8, Width, Height, Width*3, NULL, NULL);

  gtk_window_set_title (GTK_WINDOW (window), "Image Viewer");

  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  image = gtk_image_new_from_pixbuf (pixbuf);
  gtk_container_add(GTK_CONTAINER (window), image);

  gtk_widget_show_all (window);

  gtk_main ();
  // window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  // image  = gtk_image_new_from_file(input.imageName);

  // gtk_signal_connect(GTK_OBJECT (window), "destroy",
  //            GTK_SIGNAL_FUNC (destroy), NULL);

  // gtk_container_add(GTK_CONTAINER (window), image);

  // gtk_widget_show_all(window);

  // gtk_main();
}

// #include <SDL/SDL.h>
// #include <assert.h>
// #include <stdint.h>
// #include <stdlib.h>

// #define WIDTH 256
// #define HEIGHT 256

// static _Bool init_app(const char * name, SDL_Surface * icon, uint32_t flags)
// {
//     atexit(SDL_Quit);
//     if(SDL_Init(flags) < 0)
//         return 0;

//     SDL_WM_SetCaption(name, name);
//     SDL_WM_SetIcon(icon, NULL);

//     return 1;
// }

// static uint8_t * init_data(uint8_t * data)
// {
//     for(size_t i = WIDTH * HEIGHT * 3; i--; )
//         data[i] = (i % 3 == 0) ? (i / 3) % WIDTH :
//             (i % 3 == 1) ? (i / 3) / WIDTH : 0;

//     return data;
// }

// static _Bool process(uint8_t * data)
// {
//     for(SDL_Event event; SDL_PollEvent(&event);)
//         if(event.type == SDL_QUIT) return 0;

//     for(size_t i = 0; i < WIDTH * HEIGHT * 3; i += 1 + rand() % 3)
//         data[i] -= rand() % 8;

//     return 1;
// }

// static void render(SDL_Surface * sf)
// {
//     SDL_Surface * screen = SDL_GetVideoSurface();
//     if(SDL_BlitSurface(sf, NULL, screen, NULL) == 0)
//         SDL_UpdateRect(screen, 0, 0, 0, 0);
// }

// static int filter(const SDL_Event * event)
// { return event->type == SDL_QUIT; }

// #define mask32(BYTE) (*(uint32_t *)(uint8_t [4]){ [BYTE] = 0xff })

// void displayImage(struct buff input, int argc, char * argv[])
// {
  
//     (void)argc, (void)argv;
//     static uint8_t buffer[WIDTH * HEIGHT * 3];

//     _Bool ok =
//         init_app("SDL example", NULL, SDL_INIT_VIDEO) &&
//         SDL_SetVideoMode(WIDTH, HEIGHT, 24, SDL_HWSURFACE);

//     assert(ok);

//     SDL_Surface * data_sf = SDL_CreateRGBSurfaceFrom(
//         init_data(buffer), WIDTH, HEIGHT, 24, WIDTH * 3,//try adding the buffer here input.imageName
//         mask32(0), mask32(1), mask32(2), 0);

//     SDL_SetEventFilter(filter);

//     for(; process(input.imageName); SDL_Delay(10))
//         render(data_sf);

// }
