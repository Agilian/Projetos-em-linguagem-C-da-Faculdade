/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Second Edition
// Source Code Copyright (C)2004 by Jonathan S. Harbour
// Tank War Enhancement 8 - setup.c
/////////////////////////////////////////////////////////////////////////

#include "tankwar.h"

//added in chapter 15
void loadsounds()
{
    //install a digital sound driver
    if (install_sound(DIGI_AUTODETECT, MIDI_NONE, "") != 0) 
    {
        allegro_message("Error initializing sound system");
        return;
    }

    //load the ammo sound
    sounds[AMMO] = load_sample("ammo.wav");
    if (!sounds[AMMO]) 
    {
        allegro_message("Error reading ammo.wav");
        return;
    }

    //load the hit1 sound
    sounds[HIT1] = load_sample("hit1.wav");
    if (!sounds[HIT1]) 
    {
        allegro_message("Error reading hit1.wav");
        return;
    }
    //load the hit2 sound
    sounds[HIT2] = load_sample("hit2.wav");
    if (!sounds[HIT2]) 
    {
        allegro_message("Error reading hit2.wav");
        return;
    }
    //load the fire sound
    sounds[FIRE] = load_sample("fire.wav");
    if (!sounds[FIRE]) 
    {
        allegro_message("Error reading fire.wav");
        return;
    }
    //load the goopy sound
    sounds[GOOPY] = load_sample("goopy.wav");
    if (!sounds[GOOPY]) 
    {
        allegro_message("Error reading goopy.wav");
        return;
    }
    //load the harp sound
    sounds[HARP] = load_sample("harp.wav");
    if (!sounds[HARP]) 
    {
        allegro_message("Error reading harp.wav");
        return;
    }
    //load the scream sound
    sounds[SCREAM] = load_sample("scream.wav");
    if (!sounds[SCREAM]) 
    {
        allegro_message("Error reading scream.wav");
        return;
    }
    //load the ohhh sound
    sounds[OHHH] = load_sample("ohhh.wav");
    if (!sounds[OHHH]) 
    {
        allegro_message("Error reading ohhh.wav");
        return;
    }

    //cannons are reloading
    play_sample(sounds[0], VOLUME, PAN, PITCH, FALSE);

}

void loadsprites()
{
    //load explosion image
    if (explode_bmp == NULL)
    {
        explode_bmp = load_bitmap("explode.bmp", NULL);
    }

    //initialize explosion sprites
    explosions[0] = malloc(sizeof(SPRITE));
    explosions[1] = malloc(sizeof(SPRITE));

}

void setuptanks()
{
    BITMAP *temp;
    int anim;
    int n;

    //configure player 1's tank
    tanks[0] = &mytanks[0];
    tanks[0]->x = 30;
    tanks[0]->y = 40;
    tanks[0]->xspeed = 0;
    tanks[0]->dir = 3;
    tanks[0]->curframe = 0;
    tanks[0]->maxframe = 7;
    tanks[0]->framecount = 0;
    tanks[0]->framedelay = 10;
    tanks[0]->animdir = 0;
    scores[0] = 0;

    //load first tank
    temp = load_bitmap("tank1.bmp", NULL);
    for (anim=0; anim<8; anim++)
    {
        //grab animation frame
        tank_bmp[0][anim][0] = grabframe(temp, 32, 32, 0, 0, 8, anim);

        //rotate image to generate all 8 directions
        for (n=1; n<8; n++)
        {
            tank_bmp[0][anim][n] = create_bitmap(32, 32);
            clear_to_color(tank_bmp[0][anim][n], makecol(255,0,255));
            rotate_sprite(tank_bmp[0][anim][n], tank_bmp[0][anim][0], 
                0, 0, itofix(n*32));
        }

    }
    destroy_bitmap(temp);

    //configure player 2's tank
    tanks[1] = &mytanks[1];
    tanks[1]->x = SCREEN_W-30;
    tanks[1]->y = SCREEN_H-30;
    tanks[1]->xspeed = 0;
    tanks[1]->dir = 7;
    tanks[1]->curframe = 0;
    tanks[1]->maxframe = 7;
    tanks[1]->framecount = 0;
    tanks[1]->framedelay = 10;
    tanks[1]->animdir = 0;
    scores[1] = 0;

    //load second tank
    temp = load_bitmap("tank2.bmp", NULL);    
    for (anim=0; anim<8; anim++)
    {
        //grab animation frame
        tank_bmp[1][anim][0] = grabframe(temp, 32, 32, 0, 0, 8, anim);

        //rotate image to generate all 8 directions
        for (n=1; n<8; n++)
        {
            tank_bmp[1][anim][n] = create_bitmap(32, 32);
            clear_to_color(tank_bmp[1][anim][n], makecol(255,0,255));
            rotate_sprite(tank_bmp[1][anim][n], tank_bmp[1][anim][0], 
                0, 0, itofix(n*32));
        }
    }
    destroy_bitmap(temp);

    //load bullet image
    if (bullet_bmp == NULL)
        bullet_bmp = load_bitmap("bullet.bmp", NULL);

    //initialize bullets
    for (n=0; n<2; n++)
    {
       bullets[n] = &mybullets[n];
       bullets[n]->x = 0;
       bullets[n]->y = 0;
       bullets[n]->width = bullet_bmp->w;
       bullets[n]->height = bullet_bmp->h;
    }

    //center tanks inside scroll windows
    tanks[0]->x = 5 + SCROLLW/2;
    tanks[0]->y = 90 + SCROLLH/2;
    tanks[1]->x = 325 + SCROLLW/2;
    tanks[1]->y = 90 + SCROLLH/2;

}

void setupscreen()
{
    int ret;

    //set video mode    
    set_color_depth(16);
    ret = set_gfx_mode(MODE, WIDTH, HEIGHT, 0, 0);
    if (ret != 0) {
        allegro_message(allegro_error);
        return;
    }

    text_mode(-1);

    //load screen background
    back = load_bitmap("background.bmp", NULL);
    if (back == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error loading background.bmp file");
        return;
    }

    //create the double buffer
    buffer = create_bitmap(WIDTH, HEIGHT);
    if (buffer == NULL)
    {
        set_gfx_mode(GFX_TEXT, 0, 0, 0, 0);
        allegro_message("Error creating double buffer");
        return;
    }

    //position the radar
    radarx = 270;
    radary = 1;

    //position each player
    scrollx[0] = 100;
    scrolly[0] = 100;
    scrollx[1] = MAPW - 400;
    scrolly[1] = MAPH - 500;

    //position the scroll windows
    startx[0] = 5;
    starty[0] = 93;
    startx[1] = 325;
    starty[1] = 93;

}

