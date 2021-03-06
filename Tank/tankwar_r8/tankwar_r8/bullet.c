/////////////////////////////////////////////////////////////////////////
// Game Programming All In One, Second Edition
// Source Code Copyright (C)2004 by Jonathan S. Harbour
// Tank War Enhancement 8 - bullet.c
/////////////////////////////////////////////////////////////////////////

#include "tankwar.h"


void updateexplosion(int num)
{
    int x, y;

    if (!explosions[num]->alive) return;

    //draw explosion (maxframe) times
    if (explosions[num]->curframe++ < explosions[num]->maxframe)
    {
        x = explosions[num]->x;
        y = explosions[num]->y;

        //draw explosion in enemy window
        rotate_sprite(buffer, explode_bmp, 
            x + rand()%10 - 20, y + rand()%10 - 20, 
            itofix(rand()%255));

        //draw explosion in "my" window
        x = scrollx[!num] + SCROLLW/2;
        y = scrolly[!num] + SCROLLH/2;
        if (inside(x, y, 
            scrollx[num], scrolly[num], 
            scrollx[num] + SCROLLW, scrolly[num] + SCROLLH))
        {
            //draw explosion in own window if enemy is visible
            if (explosions[num]->alive)
                rotate_sprite(buffer, explode_bmp, 
                    startx[num]+x-scrollx[num] + rand()%10 - 20, 
                    starty[num]+y-scrolly[num] + rand()%10 - 20, 
                    itofix(rand()%255));
        }

    }
    else
    {
        //play "end of explosion" sound
        play_sample(sounds[HARP], VOLUME, PAN, PITCH, FALSE);

        explosions[num]->alive = 0;
        explosions[num]->curframe = 0;
    }
}

void explode(int num, int x, int y)
{
    //initialize the explosion sprite
    explosions[num]->alive = 1;
    explosions[num]->x = x;
    explosions[num]->y = y;
    explosions[num]->curframe = 0;
    explosions[num]->maxframe = 20;

    //play explosion sounds
    play_sample(sounds[GOOPY], VOLUME, PAN, PITCH, FALSE);
    play_sample(sounds[HIT1], VOLUME, PAN, PITCH, FALSE);
    play_sample(sounds[HIT2], VOLUME, PAN, PITCH, FALSE);
}

void drawbullet(int num)
{
    int n;
    int x, y;

    x = bullets[num]->x;
    y = bullets[num]->y;

    //is the bullet active?
    if (!bullets[num]->alive) return;

    //draw bullet sprite
    for (n=0; n<2; n++)
    {
        if (inside(x, y, scrollx[n], scrolly[n], 
            scrollx[n] + SCROLLW - bullet_bmp->w, 
            scrolly[n] + SCROLLH - bullet_bmp->h))
            
            //draw bullet, adjust for scroll
            draw_sprite(buffer, bullet_bmp, startx[n] + x-scrollx[n], 
                starty[n] + y-scrolly[n]);
    }

    //draw bullet on radar
    putpixel(buffer, radarx + x/10, radary + y/12, WHITE);

}

void movebullet(int num)
{
    int x, y, tx, ty;

    x = bullets[num]->x;
    y = bullets[num]->y;

    //is the bullet active?
    if (!bullets[num]->alive) return;
    
    //move bullet
    bullets[num]->x += bullets[num]->xspeed;
    bullets[num]->y += bullets[num]->yspeed;
    x = bullets[num]->x;
    y = bullets[num]->y;

    //stay within the virtual screen
    if (x < 0 || x > MAPW-6 || y < 0 || y > MAPH-6)
    {

        //play the ammo sound
        play_sample(sounds[AMMO], VOLUME, PAN, PITCH, FALSE);
        
        bullets[num]->alive = 0;
        return;
    }

    //look for a direct hit using basic collision
    tx = scrollx[!num] + SCROLLW/2;
    ty = scrolly[!num] + SCROLLH/2;
    if (inside(x,y,tx-15,ty-15,tx+15,ty+15))
    {
        //kill the bullet
        bullets[num]->alive = 0;
            
        //blow up the tank
        x = scrollx[!num] + SCROLLW/2;
        y = scrolly[!num] + SCROLLH/2;

        //draw explosion in enemy window
        explode(num, tanks[!num]->x, tanks[!num]->y);
        scores[num]++;

        //kill any "near miss" sounds
        if (num)
            stop_sample(sounds[SCREAM]);
        else
            stop_sample(sounds[OHHH]);
    }

    else if (inside(x,y,tx-30,ty-30,tx+30,ty+30))
    {
        //it's a near miss!
        if (num)
            //player 1 screams
            play_sample(sounds[SCREAM], VOLUME, PAN, PITCH, FALSE);
        else
            //player 2 ohhhs
            play_sample(sounds[OHHH], VOLUME, PAN, PITCH, FALSE);

    }
}

void fireweapon(int num)
{
    int x = scrollx[num] + SCROLLW/2;
    int y = scrolly[num] + SCROLLH/2;

    //ready to fire again?
    if (!bullets[num]->alive)
    {
        //play fire sound
        play_sample(sounds[FIRE], VOLUME, PAN, PITCH, FALSE);

        bullets[num]->alive = 1;

        //fire bullet in direction tank is facing
        switch (tanks[num]->dir)
        {
            //north
            case 0:
                bullets[num]->x = x-2;
                bullets[num]->y = y-22;
                bullets[num]->xspeed = 0;
                bullets[num]->yspeed = -BULLETSPEED;
                break;
            //NE
            case 1:
                bullets[num]->x = x+18;
                bullets[num]->y = y-18;
                bullets[num]->xspeed = BULLETSPEED;
                bullets[num]->yspeed = -BULLETSPEED;         
                break;  
            //east
            case 2:
                bullets[num]->x = x+22;
                bullets[num]->y = y-2;
                bullets[num]->xspeed = BULLETSPEED;
                bullets[num]->yspeed = 0;
                break;
            //SE
            case 3:
                bullets[num]->x = x+18;
                bullets[num]->y = y+18;
                bullets[num]->xspeed = BULLETSPEED;
                bullets[num]->yspeed = BULLETSPEED;
                break;
            //south
            case 4:
                bullets[num]->x = x-2;
                bullets[num]->y = y+22;
                bullets[num]->xspeed = 0;
                bullets[num]->yspeed = BULLETSPEED;
                break;
            //SW
            case 5:
                bullets[num]->x = x-18;
                bullets[num]->y = y+18;
                bullets[num]->xspeed = -BULLETSPEED;
                bullets[num]->yspeed = BULLETSPEED;
                break;
            //west
            case 6:
                bullets[num]->x = x-22;
                bullets[num]->y = y-2;
                bullets[num]->xspeed = -BULLETSPEED;
                bullets[num]->yspeed = 0;
                break;
            //NW
            case 7:
                bullets[num]->x = x-18;
                bullets[num]->y = y-18;
                bullets[num]->xspeed = -BULLETSPEED;
                bullets[num]->yspeed = -BULLETSPEED;
                break;
        }
    }
}
