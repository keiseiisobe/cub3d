#include "cub3d.h"

#define PADDING_CHAR '.'

void	free_2d_char(char **str)
{
	size_t	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

//map以外の情報が正しいフォーマットかどうかの確認
//6情報全てのsuffix?があるかどうかは確認できると思う。多分
//split後の二次元配列の情報が、１行２要素に収まってるかどうかは未チェック
//split後のsplited_list[i][1]がtexture, RGBなのかどうか、ファイルが開けるかは未チェック
bool	is_valid_non_map_info(char **input_, int *map_start_index)
{
	size_t	i;
	char	**splited_line;
	unsigned int info_flags = 0b000000; // == 0bNSWEFC

	i = -1;
	while (input_[++i] && info_flags != 0b111111)
	{
		if (input_[i][0] == '\n')
			continue ;
		splited_line = ft_split(input_[i], ' ');
		//splited_lineの要素が２個でない場合、エラー
		if (splited_line[0] == NULL || splited_line[1] == NULL || splited_line[2] != NULL)
		{
			printf("Invalid splited line\n");
			printf("cub3d: Error: Invalid input\n");
			free_2d_char(splited_line);
			return (false);
		}
		if (ft_strlen(splited_line[0]) == 2 && splited_line[0][0] == 'N' && splited_line[0][1] == 'O' && !(info_flags & 0b100000))
			info_flags |= 0b100000;
		else if (ft_strlen(splited_line[0]) == 2 && splited_line[0][0] == 'S' && splited_line[0][1] == 'O' && !(info_flags & 0b010000))
			info_flags |= 0b010000;
		else if (ft_strlen(splited_line[0]) == 2 && splited_line[0][0] == 'W' && splited_line[0][1] == 'E' && !(info_flags & 0b001000))
			info_flags |= 0b001000;
		else if (ft_strlen(splited_line[0]) == 2 && splited_line[0][0] == 'E' && splited_line[0][1] == 'A' && !(info_flags & 0b000100))
			info_flags |= 0b000100;
		else if (ft_strlen(splited_line[0]) == 1 && splited_line[0][0] == 'F' && !(info_flags & 0b000010))
			info_flags |= 0b000010;
		else if (ft_strlen(splited_line[0]) == 1 && splited_line[0][0] == 'C' && !(info_flags & 0b000001))
			info_flags |= 0b000001;
		else
		{
			printf("cub3d: Error: Invalid input\n");
			free_2d_char(splited_line);
			return (false);
		}
		free_2d_char(splited_line);
	}
	if (info_flags != 0b111111)
	{
		printf("here\n");
		printf("cub3d: Error: Invalid non_map info\n");
		return (false);
	}
	while (input_[i][0] == '\n')
		i++;
	*map_start_index = i;
	return (true);
}






size_t	get_map_width(char **map)
{
	size_t	i;
	size_t	max_width;
	size_t	width;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		width = ft_strlen(map[i]);
		if (width > max_width)
			max_width = width;
		i++;
	}
	return (max_width);
}

char	**add_padding(char **map, size_t map_height, size_t map_width)
{
	char	**map_padding_;
	size_t	i;
	size_t	j;

	map_padding_ = xmalloc(sizeof(char *) * (map_height + 3));
	i = -1;
	while (++i < map_height + 2)
	{
		map_padding_[i] = xmalloc(sizeof(char) * (map_width + 3));
		j = 0;
		map_padding_[i][j] = PADDING_CHAR;
		if (i == 0 || i == map_height + 1)
		{
			while (++j < map_width + 1)
				map_padding_[i][j] = PADDING_CHAR;
			map_padding_[i][j] = '\0';
			continue ;
		}
		while (++j < map_width + 1)
		{
			if (map[i][j-1] == '\0')
			{
				map_padding_[i][j] = PADDING_CHAR;
				break ;
			}
			if (map[i][j-1] != ' ' && map[i][j-1] != '\n')
				map_padding_[i][j] = map[i][j-1];
			else
				map_padding_[i][j] = PADDING_CHAR;
		}
		while (++j < map_width + 1)
			map_padding_[i][j] = PADDING_CHAR;
		map_padding_[i][j] = '\0';
	}
	map_padding_[i] = NULL;
	if (DEBUG)
	{
		printf("map_padding_ ==================\n");
		i = 0;
		while (map_padding_[i])
		{
			printf("map[%zu]: %s$\n", i%10, map_padding_[i]);
			i++;
		}
		printf("map_padding_ ==================\n");
	}
	return (map_padding_);
}

//mapが囲まれているかどうかの確認
//'.'の四方隣が'1' or '.'であるかどうか
bool	is_map_surrounded(char **map_padding_, size_t map_height, size_t map_width)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map_padding_[i])
	{
		j = 0;
		while (map_padding_[i][j])
		{
			if (map_padding_[i][j] == PADDING_CHAR)
			{
				if (i > 1 && map_padding_[i-1][j] != '1' && map_padding_[i-1][j] != PADDING_CHAR)
					return (false);
				if (i < map_height && map_padding_[i+1][j] != '1' && map_padding_[i+1][j] != PADDING_CHAR)
					return (false);
				if (j > 1 && map_padding_[i][j-1] != '1' && map_padding_[i][j-1] != PADDING_CHAR)
					return (false);
				if (j < map_width && map_padding_[i][j+1] != '1' && map_padding_[i][j+1] != PADDING_CHAR)
					return (false);
			}
			j++;
		}
		i++;
	}

	return (true);
}

//プレイヤーの人数と、mapの文字が正しいかどうかの確認
bool	char_check(char **map_padding_)
{
	size_t	i;
	size_t	j;
	size_t	player_count;

	i = 0;
	player_count = 0;
	while (map_padding_[i])
	{
		j = 0;
		while (map_padding_[i][j])
		{
			if (map_padding_[i][j] == 'N' || map_padding_[i][j] == 'S' || map_padding_[i][j] == 'W' || map_padding_[i][j] == 'E')
				player_count++;
			else if (map_padding_[i][j] != '1' && map_padding_[i][j] != '0' && map_padding_[i][j] != PADDING_CHAR)
				return (false);
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (false);
	return (true);
}

//mapの valid check
bool	is_valid_map(char **map, size_t map_height)
{
	char	**map_padding_;
	size_t	map_width;

	map_width = get_map_width(map);
	if (map_width > MAX_MAP_SIZE || map_height > MAX_MAP_SIZE)
	{
		printf("too big map\n");
		printf("cub3d: Error: Invalid map\n");
		return (false);
	}
	map_padding_ = add_padding(map, map_height, map_width);
	if (!is_map_surrounded(map_padding_, map_height, map_width))
	{
		free_2d_char(map_padding_);
		printf("map is not surrounded\n");
		printf("cub3d: Error: Invalid map\n");
		return (false);
	}
	if (!char_check(map_padding_))
	{
		free_2d_char(map_padding_);
		printf("cub3d: Error: Invalid map\n");
		return (false);
	}
	free_2d_char(map_padding_);
	return (true);
}

bool	is_valid_cub_file(char **input_, size_t input_height)
{
	char	**map;
	int		map_start_index;

	if (!is_valid_non_map_info(input_, &map_start_index))
		return (false);
	map = &input_[map_start_index-1];
	if (!is_valid_map(map, input_height - map_start_index))
		return (false);
	return (true);
}

void	is_arg_valid(int argc, char *argv[])
{
	char	**input_;
	size_t	input_height;
	//size_t	i;

	(void)argv;
	if (argc != 2)
	{
		printf("cub3d: Notice: ./cub3d [filename]\n");
		exit(EXIT_SUCCESS);
	}
	input_height = get_input_height(argv[1]);
	input_ = get_input(argv[1], input_height);
	if (!is_valid_cub_file(input_, input_height))
	{
		free_2d_char(input_);
		exit(EXIT_SUCCESS);
	}
	return ;
}
