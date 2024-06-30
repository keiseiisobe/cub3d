#include "cub3d.h"

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
bool	is_valid_non_map_info(char **input_)
{
	size_t	i;
	size_t	k;
	char	**splited_line;
	unsigned int info_flags = 0b000000; // 6桁の2進数で、各情報があるかどうかを示す
	// 0b000000 0bNSWEFC
	i = 0;
	while (info_flags != 0b111111 && input_[i])
	{
		if (input_[i][0] == '\n')
			continue ;
		splited_line = ft_split(input_[i], ' ');
		//splited_lineの要素が２個でない場合、エラー
		if (splited_line[0] == NULL || splited_line[1] == NULL || splited_line[2] != NULL)
		{
			printf("cub3d: Error: Invalid input\n");
			return (false);
		}
		if (ft_strlen(splited_line[0]) == 2 && splited_line[0][0] == 'N' && splited_line[0][1] == 'O')
			info_flags |= 0b100000;
		else if (ft_strlen(splited_line[0]) == 2 && splited_line[0][0] == 'S' && splited_line[0][1] == 'O')
			info_flags |= 0b010000;
		else if (ft_strlen(splited_line[0]) == 2 && splited_line[0][0] == 'W' && splited_line[0][1] == 'E')
			info_flags |= 0b001000;
		else if (ft_strlen(splited_line[0]) == 2 && splited_line[0][0] == 'E' && splited_line[0][1] == 'A')
			info_flags |= 0b000100;
		else if (ft_strlen(splited_line[0]) == 1 && splited_line[0][0] == 'F')
			info_flags |= 0b000010;
		else if (ft_strlen(splited_line[0]) == 1 && splited_line[0][0] == 'C')
			info_flags |= 0b000001;
		k = 0;
		while (splited_line[k])
			free(splited_line[k++]);
		free(splited_line);
		i++;
	}
	if (info_flags != 0b111111)
	{
		printf("cub3d: Error: Invalid non_map info\n");
		return (false);
	}
	return (true);
}

//mapが囲まれてるかどうかとかを判定
bool	is_valid_map(char **map)
{
	if (map)
		;
	return (true);
}

bool is_valid_cub_file(char **input_, int input_height)
{
	char	**map;
	int	i;
	size_t	count6;

	if (!is_valid_non_map_info(input_))
		return (false);
	i = -1;
	count6 = 0;
	while (i < input_height+1 && count6 < 6)
	{
		i++;
		if (input_[i][0] == '\n')
			continue ;
		count6++;
	}
	i++;
	while (input_[i][0] == '\n')
		i++;
	if (input_[i] == NULL)
		return (false);
	map = &input_[i];
	if (!is_valid_map(map))
		return (false);
	return (true);
}

void	is_arg_valid(int argc, char *argv[])
{
	char	**input_;
	size_t	input_height;
	size_t	i;

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
		i = 0;
		while (i < input_height)
			free(input_[i++]);
		free(input_);
		exit(EXIT_SUCCESS);
	}
	// is_file_valid(); ex. suffix, empty, surrounded by wall
	return ;
}
