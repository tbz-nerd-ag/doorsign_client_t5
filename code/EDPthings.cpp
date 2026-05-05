#include <Arduino.h>

#include "epd_driver.h"
#include "utilities.h"
#include "firasans.h"

#include <header.h>

void errormenu(int menu) {
    if (menu == 1) {
        int cursor_x = 30;
        int cursor_y = 60;
        String txt = "";

        epd_poweron();
        epd_clear();

        write_string((GFXfont *)&FiraSans, "Doorsign Display Error", &cursor_x, &cursor_y, framebuffer);
        epd_draw_hline(10, 70, EPD_WIDTH - 20, 0, framebuffer);
        cursor_y = 120, cursor_x = 30;
        write_string((GFXfont *)&FiraSans, "Dem Display ist kein Raum hinterlegt!", &cursor_x, &cursor_y, framebuffer);
        cursor_y = 160, cursor_x = 30;  
        write_string((GFXfont *)&FiraSans, "Bitte über den Server einrichten!", &cursor_x, &cursor_y, framebuffer);

        cursor_y = 280, cursor_x = 30;
        write_string((GFXfont *)&FiraSans, "Informationen:", &cursor_x, &cursor_y, framebuffer);

        cursor_y = 320, cursor_x = 30;
        txt = "SSID: " + ssid;
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 360, cursor_x = 30;
        txt = "Display ID: " + String(id);
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 400, cursor_x = 30;
        txt = "IP: " + IP;
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 440, cursor_x = 30;
        txt = "MAC: " + MAC;
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 520, cursor_x = 30;
        txt = "Aktualsiert am: " + String(time_str);
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        epd_draw_grayscale_image(epd_full_screen(), framebuffer);
        epd_poweroff();
    }else if (menu == 2) {
        int cursor_x = 30;
        int cursor_y = 60;
        String txt = "";

        epd_poweron();
        epd_clear();

        write_string((GFXfont *)&FiraSans, "Doorsign Display Error", &cursor_x, &cursor_y, framebuffer);
        epd_draw_hline(10, 70, EPD_WIDTH - 20, 0, framebuffer);
        cursor_y = 120, cursor_x = 30;
        write_string((GFXfont *)&FiraSans, "Das Display kann sich nicht mit dem WLAN", &cursor_x, &cursor_y, framebuffer);
        cursor_y = 160, cursor_x = 30;
        write_string((GFXfont *)&FiraSans, "Verbinden! Bitte überprüfe das!", &cursor_x, &cursor_y, framebuffer);

        cursor_y = 280, cursor_x = 30;
        write_string((GFXfont *)&FiraSans, "Informationen:", &cursor_x, &cursor_y, framebuffer);

        cursor_y = 320, cursor_x = 30;
        txt = "SSID: " + ssid;
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 360, cursor_x = 30;
        txt = "Display ID: " + String(id);
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        epd_draw_grayscale_image(epd_full_screen(), framebuffer);
        epd_poweroff();
    }else if (menu == 3) {
        int cursor_x = 30;
        int cursor_y = 60;
        String txt = "";

        epd_poweron();
        epd_clear();

        write_string((GFXfont *)&FiraSans, "Doorsign Display Error", &cursor_x, &cursor_y, framebuffer);
        epd_draw_hline(10, 70, EPD_WIDTH - 20, 0, framebuffer);
        cursor_y = 120, cursor_x = 30;
        write_string((GFXfont *)&FiraSans, "MQTT Server nicht ereichbar!", &cursor_x, &cursor_y, framebuffer);
        txt = "MQTT Server: " + String(broker);
        cursor_y = 160, cursor_x = 30;
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 280, cursor_x = 30;
        write_string((GFXfont *)&FiraSans, "Informationen:", &cursor_x, &cursor_y, framebuffer);

        cursor_y = 320, cursor_x = 30;
        txt = "SSID: " + ssid;
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 360, cursor_x = 30;
        txt = "Display ID: " + String(id);
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 400, cursor_x = 30;
        txt = "IP: " + IP;
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 440, cursor_x = 30;
        txt = "MAC: " + MAC;
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        cursor_y = 520, cursor_x = 30;
        txt = "Aktualsiert am: " + String(time_str);
        write_string((GFXfont *)&FiraSans, txt.c_str(), &cursor_x, &cursor_y, framebuffer);

        epd_draw_grayscale_image(epd_full_screen(), framebuffer);
        epd_poweroff();
    }
}
void testepdscreen() {
    
}
