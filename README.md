# cub3D

## Usage
```bash
make
./cub3D map.cub
```
## arguments
*.cub  <a map cosists of the following elements>
- 0 : empty space
- 1 : wall

## OK functions
- open
- close
- read
- write
- printf
- malloc
- free
- perror
- strerror
- exit
- gettimeofday
- All functions of the math library (-lm man man 3 math)
- All functions of the MinilibX
- Libft functions

# ===== devlogs =====
### 2024/06/20 kisobe
- To compile, change "# include "../mlx-mms/mlx.h" in include/cub3d.h to # include "../mlx-linux/mlx.h"" and remove libmlx.dylib.
### 2024/06/21 kisobe
- Implemented event hook(W, A, S, D, ->, <-)
- floor and ceiling color
- wall collisions
- added event.c and move.c

### 2024/06/25 kmiyazaw
- 日本語で失礼します
-

