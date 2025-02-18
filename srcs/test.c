/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kjung <kjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:13:32 by kjung             #+#    #+#             */
/*   Updated: 2025/02/18 16:53:21 by kjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "key_linux.h"
#include "../includes/cub3d.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define KEY_PRESS_MASK	1L<<0
#define mapWidth 24
#define mapHeight 24

// typedef struct	s_img
// {
// 	void	*img;
// 	int		*data;

// 	int		size_l;
// 	int		bpp;
// 	int		endian;
// 	int		img_width;
// 	int		img_height;
// }				t_img;

void draw(t_cub *cub)
{
    static int first_draw = 1;
    if (first_draw)
    {
        printf("Draw function called, using calc buffer\n");
        first_draw = 0;
    }

    // calc 함수의 버퍼를 화면에 그리기
    for (int y = 0; y < SCREEN_HEIGHT; y++)
    {
        for (int x = 0; x < SCREEN_WIDTH; x++)
        {
            my_mlx_pixel_put(cub->data, x, y, cub->ray.buf[y][x]);
        }
    }
    
    mlx_put_image_to_window(cub->data->mlx, cub->data->win, cub->data->img.img, 0, 0);
}

void calc(t_cub *cub)
{
   static int first_calc = 1;
   if (first_calc)
   {
       printf("\n===== First Calc Call =====\n");
       printf("Player position: (%f, %f)\n", cub->ray.pos_x, cub->ray.pos_y);
       printf("Direction: (%f, %f)\n", cub->ray.dir_x, cub->ray.dir_y);
       printf("Camera plane: (%f, %f)\n", cub->ray.plane_x, cub->ray.plane_y);
       printf("Map dimensions: %d x %d\n", cub->ray.map_width, cub->ray.map_height);
       first_calc = 0;
   }

   for(int x = 0; x < SCREEN_WIDTH; x++)
   {
       double cameraX = 2 * x / (double)SCREEN_WIDTH - 1;
       double raydir_x = cub->ray.dir_x + cub->ray.plane_x * cameraX;
       double rayDirY = cub->ray.dir_y + cub->ray.plane_y * cameraX;

       int mapX = (int)cub->ray.pos_x;
       int mapY = (int)cub->ray.pos_y;

       double deltaDistX = (raydir_x == 0) ? 1e30 : fabs(1 / raydir_x);
       double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

       double sideDistX;
       double sideDistY;
       
       int stepX = (raydir_x < 0) ? -1 : 1;
       int stepY = (rayDirY < 0) ? -1 : 1;

       if (raydir_x < 0)
           sideDistX = (cub->ray.pos_x - mapX) * deltaDistX;
       else
           sideDistX = (mapX + 1.0 - cub->ray.pos_x) * deltaDistX;
       if (rayDirY < 0)
           sideDistY = (cub->ray.pos_y - mapY) * deltaDistY;
       else
           sideDistY = (mapY + 1.0 - cub->ray.pos_y) * deltaDistY;

       int hit = 0;
       int side = 0;
       while (hit == 0)
       {
           int nextMapX = mapX;
           int nextMapY = mapY;
           
           if (sideDistX < sideDistY)
           {
               sideDistX += deltaDistX;
               nextMapX = mapX + stepX;
               side = 0;
           }
           else
           {
               sideDistY += deltaDistY;
               nextMapY = mapY + stepY;
               side = 1;
           }
           
           if (nextMapX < 0 || nextMapX >= cub->ray.map_width || 
               nextMapY < 0 || nextMapY >= cub->ray.map_height)
           {
               hit = 1;
               break;
           }
           
           mapX = nextMapX;
           mapY = nextMapY;
           
           if (cub->ray.world_map[mapY][mapX] > 0)
               hit = 1;
       }

       double perpWallDist;
       if (side == 0)
           perpWallDist = (mapX - cub->ray.pos_x + (1 - stepX) / 2) / raydir_x;
       else
           perpWallDist = (mapY - cub->ray.pos_y + (1 - stepY) / 2) / rayDirY;

       int lineHeight = (int)(SCREEN_HEIGHT / perpWallDist);

       int drawStart = -lineHeight / 2 + SCREEN_HEIGHT / 2;
       if (drawStart < 0) drawStart = 0;
       int drawEnd = lineHeight / 2 + SCREEN_HEIGHT / 2;
       if (drawEnd >= SCREEN_HEIGHT) drawEnd = SCREEN_HEIGHT - 1;

       // 텍스처 계산
       double wallX;
       if (side == 0)
           wallX = cub->ray.pos_y + perpWallDist * rayDirY;
       else
           wallX = cub->ray.pos_x + perpWallDist * raydir_x;
       wallX -= floor(wallX);

       int texX = (int)(wallX * (double)texWidth);
       if (side == 0 && raydir_x > 0) texX = texWidth - texX - 1;
       if (side == 1 && rayDirY < 0) texX = texWidth - texX - 1;

       // 텍스처 적용
       int texNum;
       if (side == 0)
           texNum = (raydir_x > 0) ? 0 : 1;  // east/west
       else
           texNum = (rayDirY > 0) ? 2 : 3;  // south/north

       // 천장
       for(int y = 0; y < drawStart; y++)
           cub->ray.buf[y][x] = 0x444444;

       // 벽 (텍스처 적용)
       double step = 1.0 * texHeight / lineHeight;
       double texPos = (drawStart - SCREEN_HEIGHT / 2 + lineHeight / 2) * step;
       
       for(int y = drawStart; y < drawEnd; y++)
       {
           int texY = (int)texPos & (texHeight - 1);
           texPos += step;

           int color = cub->data->textures[texNum][texHeight * texY + texX];
           if (side == 1)
               color = (color >> 1) & 8355711;  // 어둡게
           cub->ray.buf[y][x] = color;
       }

       // 바닥
       for(int y = drawEnd; y < SCREEN_HEIGHT; y++)
           cub->ray.buf[y][x] = 0x888888;
   }
}

int main_loop(t_cub **cub)
{
    static int frame_count = 0;
    frame_count++;
    
    if (frame_count == 1)
        printf("First frame rendering started\n");
        
    calc(*cub);  // 레이캐스팅 다시 활성화
    draw(*cub);
    
    if (frame_count == 1)
        printf("First frame completed\n");
        
    return (0);
}

// int key_press(int key, t_cub *cub)
// {
//     // W키 (앞으로)
//     if (key == 119)
//     {
//         int newX = (int)(cub->ray.pos_x + cub->ray.dir_x * cub->ray.move_speed);
//         int newY = (int)(cub->ray.pos_y + cub->ray.dir_y * cub->ray.move_speed);
        
//         // 맵 경계 체크 수정 (x,y 순서 변경)
//         if (newX >= 0 && newX < cub->ray.map_width && 
//             (int)cub->ray.pos_y >= 0 && (int)cub->ray.pos_y < cub->ray.map_height &&
//             !cub->ray.world_map[(int)cub->ray.pos_y][newX])  // 순서 변경
//             cub->ray.pos_x += cub->ray.dir_x * cub->ray.move_speed;
            
//         if ((int)cub->ray.pos_x >= 0 && (int)cub->ray.pos_x < cub->ray.map_width && 
//             newY >= 0 && newY < cub->ray.map_height &&
//             !cub->ray.world_map[newY][(int)cub->ray.pos_x])  // 순서 변경
//             cub->ray.pos_y += cub->ray.dir_y * cub->ray.move_speed;
//     }
//     // S키 (뒤로) - 같은 방식으로 수정
//     if (key == 115)
//     {
//         int newX = (int)(cub->ray.pos_x - cub->ray.dir_x * cub->ray.move_speed);
//         int newY = (int)(cub->ray.pos_y - cub->ray.dir_y * cub->ray.move_speed);
        
//         if (newX >= 0 && newX < cub->ray.map_width && 
//             (int)cub->ray.pos_y >= 0 && (int)cub->ray.pos_y < cub->ray.map_height &&
//             !cub->ray.world_map[(int)cub->ray.pos_y][newX])
//             cub->ray.pos_x -= cub->ray.dir_x * cub->ray.move_speed;
            
//         if ((int)cub->ray.pos_x >= 0 && (int)cub->ray.pos_x < cub->ray.map_width && 
//             newY >= 0 && newY < cub->ray.map_height &&
//             !cub->ray.world_map[newY][(int)cub->ray.pos_x])
//             cub->ray.pos_y -= cub->ray.dir_y * cub->ray.move_speed;
//     }
//     // 회전 방향 수정 (A키 - 왼쪽)
//     if (key == 97)  // A키
//     {
//         double olddir_x = cub->ray.dir_x;
//         cub->ray.dir_x = cub->ray.dir_x * cos(-cub->ray.rot_speed) - cub->ray.dir_y * sin(-cub->ray.rot_speed);
//         cub->ray.dir_y = olddir_x * sin(-cub->ray.rot_speed) + cub->ray.dir_y * cos(-cub->ray.rot_speed);
//         double oldPlaneX = cub->ray.plane_x;
//         cub->ray.plane_x = cub->ray.plane_x * cos(-cub->ray.rot_speed) - cub->ray.plane_y * sin(-cub->ray.rot_speed);
//         cub->ray.plane_y = oldPlaneX * sin(-cub->ray.rot_speed) + cub->ray.plane_y * cos(-cub->ray.rot_speed);
//     }
//     // D키 - 오른쪽
//     if (key == 100)
//     {
//         double olddir_x = cub->ray.dir_x;
//         cub->ray.dir_x = cub->ray.dir_x * cos(cub->ray.rot_speed) - cub->ray.dir_y * sin(cub->ray.rot_speed);
//         cub->ray.dir_y = olddir_x * sin(cub->ray.rot_speed) + cub->ray.dir_y * cos(cub->ray.rot_speed);
//         double oldPlaneX = cub->ray.plane_x;
//         cub->ray.plane_x = cub->ray.plane_x * cos(cub->ray.rot_speed) - cub->ray.plane_y * sin(cub->ray.rot_speed);
//         cub->ray.plane_y = oldPlaneX * sin(cub->ray.rot_speed) + cub->ray.plane_y * cos(cub->ray.rot_speed);
//     }
//     if (key == 65307)
//         exit(0);
//     return (0);
// }

// void load_texture(t_cub *cub)
// {
//     printf("\n===== Texture Debug Info =====\n");
//     printf("NO texture path: %s\n", cub->file->no_dir);
//     printf("SO texture path: %s\n", cub->file->so_dir);
//     printf("WE texture path: %s\n", cub->file->we_dir);
//     printf("EA texture path: %s\n", cub->file->ea_dir);
    
//     // 텍스처 메모리 할당
//     if (!(cub->ray.texture = (int **)malloc(sizeof(int *) * 8)))
//     {
//         printf("Texture array allocation failed\n");
//         return;
//     }

//     // 각 텍스처에 대해 메모리 할당 및 초기 색상 설정
//     for (int i = 0; i < 8; i++)
//     {
//         if (!(cub->ray.texture[i] = (int *)malloc(sizeof(int) * (texHeight * texWidth))))
//         {
//             printf("Texture %d allocation failed\n", i);
//             for (int j = 0; j < i; j++)
//                 free(cub->ray.texture[j]);
//             free(cub->ray.texture);
//             return;
//         }
        
//         // 임시로 각 텍스처에 다른 색상 설정
//         int color;
//         switch(i) {
//             case 0: color = 0xFF0000; break;  // 북쪽 벽 - 빨강
//             case 1: color = 0x00FF00; break;  // 남쪽 벽 - 초록
//             case 2: color = 0x0000FF; break;  // 서쪽 벽 - 파랑
//             case 3: color = 0xFFFF00; break;  // 동쪽 벽 - 노랑
//             default: color = 0x888888;        // 기타 - 회색
//         }
        
//         for (int j = 0; j < texHeight * texWidth; j++)
//             cub->ray.texture[i][j] = color;
//     }
//     printf("Temporary textures initialized\n");
// }

// void load_image(t_cub *cub, int *texture, char *path)
// {
//     printf("Loading image from path: %s\n", path);
//     t_img img;
//     int bits_per_pixel;
//     int line_length;
//     int endian;
    
//     img.img = mlx_xpm_file_to_image(cub->data->mlx, path, &img.img_width, &img.img_height);
//     if (!img.img)
//     {
//         printf("Failed to load image: %s\n", path);
//         return;
//     }

//     img.data = (int *)mlx_get_data_addr(img.img, &bits_per_pixel, 
//                                        &line_length, &endian);
//     if (!img.data)
//     {
//         printf("Failed to get image data\n");
//         mlx_destroy_image(cub->data->mlx, img.img);
//         return;
//     }

//     for (int y = 0; y < texHeight; y++)
//     {
//         for (int x = 0; x < texWidth; x++)
//         {
//             texture[texWidth * y + x] = img.data[img.img_width * y + x];
//         }
//     }
    
//     mlx_destroy_image(cub->data->mlx, img.img);
//     printf("Image loaded successfully\n");
// }

int	close_window(void *param)
{
    (void)param;
    exit(0);
    return (0);
}

int init_world_map(t_cub *cub)
{
    cub->ray.map_height = cub->file->map_height;
    cub->ray.map_width = cub->file->map_width;
    
    cub->ray.world_map = (int **)malloc(sizeof(int *) * cub->ray.map_height);
    if (!cub->ray.world_map)
        return (0);
        
    for (int i = 0; i < cub->ray.map_height; i++)
    {
        cub->ray.world_map[i] = (int *)malloc(sizeof(int) * cub->ray.map_width);
        if (!cub->ray.world_map[i])
        {
            // 이미 할당된 메모리 해제
            for (int j = 0; j < i; j++)
                free(cub->ray.world_map[j]);
            free(cub->ray.world_map);
            return (0);
        }
            
        for (int j = 0; j < cub->ray.map_width; j++)
        {
            if (cub->file->maparr[i][j] == '1')
                cub->ray.world_map[i][j] = 1;
            else if (cub->file->maparr[i][j] == ' ')
                cub->ray.world_map[i][j] = 1;  // 공백은 벽으로 처리
            else
                cub->ray.world_map[i][j] = 0;
        }
    }
    
    return (1);  // 성공적으로 초기화 완료
}

int init_ray_info(t_cub *cub)
{
    printf("Starting ray info initialization...\n");
    printf("File pos_x: %f, pos_y: %f\n", cub->file->pos_x, cub->file->pos_y);
    printf("Map dimensions: %d x %d\n", cub->ray.map_width, cub->ray.map_height);
    
    // 위치 유효성 검사
    if (cub->file->pos_x < 0 || cub->file->pos_x >= cub->ray.map_width ||
        cub->file->pos_y < 0 || cub->file->pos_y >= cub->ray.map_height)
    {
        printf("Error: Invalid player position (%f, %f) for map size %dx%d\n",
               cub->file->pos_x, cub->file->pos_y,
               cub->ray.map_width, cub->ray.map_height);
        return (0);
    }
    
    cub->ray.pos_x = cub->file->pos_x;
    cub->ray.pos_y = cub->file->pos_y;
	memset(cub->ray.buf, 0, sizeof(cub->ray.buf));
    printf("Player direction: %c\n", cub->file->pos_dir);
    // 방향 초기화
    if (cub->file->pos_dir == '4')  // North
    {
        cub->ray.dir_x = 0.0;
        cub->ray.dir_y = -1.0;
        cub->ray.plane_x = 0.66;
        cub->ray.plane_y = 0.0;
    }
    else if (cub->file->pos_dir == '3')  // South 
    {
        cub->ray.dir_x = 0.0;
        cub->ray.dir_y = 1.0;
        cub->ray.plane_x = -0.66;
        cub->ray.plane_y = 0.0;
    }
    else if (cub->file->pos_dir == '1')  // East
    {
        cub->ray.dir_x = 1.0;
        cub->ray.dir_y = 0.0;
        cub->ray.plane_x = 0.0;
        cub->ray.plane_y = 0.66;
    }
    else if (cub->file->pos_dir == '2')  // West
    {
        cub->ray.dir_x = -1.0;
        cub->ray.dir_y = 0.0;
        cub->ray.plane_x = 0.0;
        cub->ray.plane_y = -0.66;
    }
    else
    {
        printf("Invalid direction value\n");
        return (0);
    }

    printf("Player position: (%f, %f)\n", cub->ray.pos_x, cub->ray.pos_y);
    printf("Player direction: (%f, %f)\n", cub->ray.dir_x, cub->ray.dir_y);
    printf("Camera plane: (%f, %f)\n", cub->ray.plane_x, cub->ray.plane_y);

    cub->ray.move_speed = MOVE_SPEED;
    cub->ray.rot_speed = ROT_SPEED;

    return (1);
}

void debug_cub(t_cub *cub)
{
    printf("MLX: %p\n", cub->data->mlx);
    printf("Window: %p\n", cub->data->win);
    printf("Map width: %d\n", cub->ray.map_width);
    printf("Map height: %d\n", cub->ray.map_height);
    printf("Player pos: (%f, %f)\n", cub->ray.pos_x, cub->ray.pos_y);
}

int main(int argc, char **argv)
{
   t_cub   *cub;
   
   cub = malloc(sizeof(t_cub));
   cub->data = malloc(sizeof(t_data));
   cub->file = NULL;
   
   printf("===== MLX 초기화 시작 =====\n");
   ft_mlx_init(cub->data);
   printf("MLX: %p\n", cub->data->mlx);
   printf("Window: %p\n", cub->data->win);

   printf("\n===== 파일 파싱 시작 =====\n");
   ft_parse_file(argc, argv, &(cub->file));

   printf("\n===== World Map 초기화 시작 =====\n");
   if (!init_world_map(cub))
   {
       printf("Error: World map initialization failed\n");
       return (-1);
   }
   printf("Map dimensions: %d x %d\n", cub->ray.map_width, cub->ray.map_height);

   printf("\n===== Ray Info 초기화 시작 =====\n");
   if (!init_ray_info(cub))
   {
       printf("Error: Ray info initialization failed\n");
       return (-1);
   }
   printf("Player position: (%f, %f)\n", cub->ray.pos_x, cub->ray.pos_y);
   printf("Player direction: (%f, %f)\n", cub->ray.dir_x, cub->ray.dir_y);
   printf("Camera plane: (%f, %f)\n", cub->ray.plane_x, cub->ray.plane_y);
   
   printf("\n===== 텍스처 로딩 시작 =====\n");
	ft_read_cub_value(&(cub->file), &cub);	

   printf("\n===== MLX Loop 시작 =====\n");
   mlx_loop_hook(cub->data->mlx, (void *)main_loop, &cub);
   mlx_hook(cub->data->win, X_EVENT_KEY_PRESS, KEY_PRESS_MASK, key_press, cub);
   mlx_hook(cub->data->win, X_EVENT_KEY_EXIT, 0, close_window, cub);
   
   printf("Starting MLX loop...\n");
   mlx_loop(cub->data->mlx);
   
   return (0);
}
