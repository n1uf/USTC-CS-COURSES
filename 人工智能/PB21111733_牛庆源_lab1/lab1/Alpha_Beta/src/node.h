#include <vector>
#include <map>
#include <limits>
#include <iostream>
#include <string>

namespace ChineseChess
{
    //棋力评估，这里的棋盘方向和输入棋盘方向不同，在使用时需要仔细
    //生成合法动作代码部分已经使用，经过测试是正确的，大家可以参考
    std::vector<std::vector<int>> JiangPosition = {
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {1, -8, -9, 0, 0, 0, 0, 0, 0, 0},
                                                {5, -8, -9, 0, 0, 0, 0, 0, 0, 0},
                                                {1, -8, -9, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            };

    std::vector<std::vector<int>> ShiPosition = {
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 3, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                            };
        
    std::vector<std::vector<int>> XiangPosition = {
                                                {0, 0, -2, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                                {0, 0, -2, 0, 0, 0, 0, 0, 0, 0},
                                            };

    std::vector<std::vector<int>> MaPosition = {
                                                {0, -3, 5, 4, 2, 2, 5, 4, 2, 2},
                                                {-3, 2, 4, 6, 10, 12, 20, 10, 8, 2},
                                                {2, 4, 6, 10, 13, 11, 12, 11, 15, 2},
                                                {0, 5, 7, 7, 14, 15, 19, 15, 9, 8},
                                                {2, -10, 4, 10, 15, 16, 12, 11, 6, 2},
                                                {0, 5, 7, 7, 14, 15, 19, 15, 9, 8},
                                                {2, 4, 6, 10, 13, 11, 12, 11, 15, 2},
                                                {-3, 2, 4, 6, 10, 12, 20, 10, 8, 2},
                                                {0, -3, 5, 4, 2, 2, 5, 4, 2, 2},
                                            };

    std::vector<std::vector<int>> PaoPosition = {
                                                {0, 0, 1, 0, -1, 0, 0, 1, 2, 4},
                                                {0, 1, 0, 0, 0, 0, 3, 1, 2, 4},
                                                {1, 2, 4, 0, 3, 0, 3, 0, 0, 0},
                                                {3, 2, 3, 0, 0, 0, 2, -5, -4, -5},
                                                {3, 2, 5, 0, 4, 4, 4, -4, -7, -6},
                                                {3, 2, 3, 0, 0, 0, 2, -5, -4, -5},
                                                {1, 2, 4, 0, 3, 0, 3, 0, 0, 0},
                                                {0, 1, 0, 0, 0, 0, 3, 1, 2, 4},
                                                {0, 0, 1, 0, -1, 0, 0, 1, 2, 4},
                                            };

    std::vector<std::vector<int>> JuPosition = {
                                                {-6, 5, -2, 4, 8, 8, 6, 6, 6, 6},
                                                {6, 8, 8, 9, 12, 11, 13, 8, 12, 8},
                                                {4, 6, 4, 4, 12, 11, 13, 7, 9, 7},
                                                {12, 12, 12, 12, 14, 14, 16, 14, 16, 13},
                                                {0, 0, 12, 14, 15, 15, 16, 16, 33, 14},
                                                {12, 12, 12, 12, 14, 14, 16, 14, 16, 13},
                                                {4, 6, 4, 4, 12, 11, 13, 7, 9, 7},
                                                {6, 8, 8, 9, 12, 11, 13, 8, 12, 8},
                                                {-6, 5, -2, 4, 8, 8, 6, 6, 6, 6},
                                            };

    std::vector<std::vector<int>> BingPosition = {
                                                {0, 0, 0, -2, 3, 10, 20, 20, 20, 0},
                                                {0, 0, 0, 0, 0, 18, 27, 30, 30, 0},
                                                {0, 0, 0, -2, 4, 22, 30, 45, 50, 0},
                                                {0, 0, 0, 0, 0, 35, 40, 55, 65, 2},
                                                {0, 0, 0, 6, 7, 40, 42, 55, 70, 4},
                                                {0, 0, 0, 0, 0, 35, 40, 55, 65, 2},
                                                {0, 0, 0, -2, 4, 22, 30, 45, 50, 0},
                                                {0, 0, 0, 0, 0, 18, 27, 30, 30, 0},
                                                {0, 0, 0, -2, 3, 10, 20, 20, 20, 0},
                                            };

    //棋子价值评估
    std::map<std::string, int> piece_values = {
                                            {"Jiang", 10000},
                                            {"Shi", 10},
                                            {"Xiang", 30},
                                            {"Ma", 300},
                                            {"Ju", 500},
                                            {"Pao", 300},
                                            {"Bing", 90}
                                        };

    //行期可能性评估，这里更多是对下一步动作的评估
    std::map<std::string, int> next_move_values = {
                                            {"Jiang", 9999},
                                            {"Ma", 100},
                                            {"Ju", 500},
                                            {"Pao", 100},
                                            {"Bing", -20}
                                        };
    
    //动作结构体，每个动作设置score，可以方便剪枝
    struct Move {
        int init_x;
        int init_y;
        int next_x;
        int next_y;
        int score;
    };

    // 定义棋盘上的棋子结构体
    struct ChessPiece {
        char name; // 棋子名称
        int init_x, init_y; // 棋子的坐标
        bool color;   //棋子阵营 true为红色、false为黑色
    };

    // 定义棋盘类
    class ChessBoard {
    private:
        int sizeX, sizeY;   //棋盘大小，固定
        std::vector<ChessPiece> pieces;   //棋盘上所有棋子
        std::vector<std::vector<char>> board;    //当前棋盘、二维数组表示
        std::vector<Move> red_moves;    //红方棋子的合法动作
        std::vector<Move> black_moves;   //黑方棋子的合法动作
    public:
        // 初始化棋盘，提取棋盘上棋子，并生成所有合法动作
        void initializeBoard(const std::vector<std::vector<char>>& init_board) {
            board = init_board;
            sizeX = board.size();
            sizeY = board[0].size();

            for (int i = 0; i < sizeX; ++i) {
                for (int j = 0; j < sizeY; ++j) {
                    char pieceChar = board[i][j];
                    if (pieceChar == '.') continue;

                    ChessPiece piece;
                    piece.init_x = i;
                    piece.init_y = j;
                    piece.color = (pieceChar >= 'A' && pieceChar <= 'Z');
                    piece.name = pieceChar;
                    pieces.push_back(piece);

                    switch (pieceChar) {
                        case 'R':
                            generateJuMoves(i, j, piece.color);
                            break;
                        case 'C':
                            generatePaoMoves(i, j, piece.color);
                            break;
                        case 'N':
                            generateMaMoves(i, j, piece.color);
                            break;
                        case 'B':
                            generateXiangMoves(i, j, piece.color);
                            break;
                        case 'A':
                            generateShiMoves(i, j, piece.color);
                            break;
                        case 'K':
                            generateJiangMoves(i, j, piece.color);
                            break;
                        case 'P':
                            generateBingMoves(i, j, piece.color);
                            break;
                        case 'r':
                            generateJuMoves(i, j, piece.color);
                            break;
                        case 'c':
                            generatePaoMoves(i, j, piece.color);
                            break;
                        case 'n':
                            generateMaMoves(i, j, piece.color);
                            break;
                        case 'b':
                            generateXiangMoves(i, j, piece.color);
                            break;
                        case 'a':
                            generateShiMoves(i, j, piece.color);
                            break;
                        case 'k':
                            generateJiangMoves(i, j, piece.color);
                            break;
                        case 'p':
                            generateBingMoves(i, j, piece.color);
                            break;
                        default:
                            break;
                    }
                } 
            }
        }
        
        //生成车的合法动作
        void generateJuMoves(int x, int y, bool color) {
            //前后左右分别进行搜索，遇到棋子停止，不同阵营可以吃掉
            std::vector<Move> JuMoves;
            for(int i = x + 1; i < sizeX; i++) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                if (board[i][y] != '.') {
                    bool cur_color = (board[i][y] >= 'A' && board[i][y] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move);
            }

            for(int i = x - 1; i >= 0; i--) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                if (board[i][y] != '.') {
                    bool cur_color = (board[i][y] >= 'A' && board[i][y] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move);
            }

            for(int j = y + 1; j < sizeY; j++) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = x;
                cur_move.next_y = j;
                cur_move.score = 0;
                if (board[x][j] != '.') {
                    bool cur_color = (board[x][j] >= 'A' && board[x][j] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move);
            }

            for(int j = y - 1; j >= 0; j--) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = x;
                cur_move.next_y = j;
                cur_move.score = 0;
                if (board[x][j] != '.') {
                    bool cur_color = (board[x][j] >= 'A' && board[x][j] <= 'Z');
                    if (cur_color != color) {
                        JuMoves.push_back(cur_move);
                    }
                    break;
                }
                JuMoves.push_back(cur_move); 
            }
            for (int i = 0; i < JuMoves.size(); i++) {
                if(color) {
                    JuMoves[i].score = JuPosition[JuMoves[i].next_y][9-JuMoves[i].next_x] - JuPosition[y][9-x];
                    red_moves.push_back(JuMoves[i]);
                }
                else {
                    JuMoves[i].score = JuPosition[JuMoves[i].next_y][JuMoves[i].next_x] - JuPosition[y][x];
                    black_moves.push_back(JuMoves[i]);
                }
            }
        }

        //生成马的合法动作
        void generateMaMoves(int x, int y, bool color) {
            //便利所有可能动作，筛选
            std::vector<Move> MaMoves;
            int dx[] = {2, 1, -1, -2, -2, -1, 1, 2};
            int dy[] = {1, 2, 2, 1, -1, -2, -2, -1};
            int obstacle_x[] = {1, 0, 0, -1, -1, 0, 0, 1};
            int obstacle_y[] = {0, 1, 1, 0, 0, -1, -1, 0};
            //简化，不考虑拌马脚
            //TODO 可以实现拌马脚过程
            for(int i = 0; i < 8; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= 10 || ny < 0 || ny >= 9) continue;
                if (board[x + obstacle_x[i]][y + obstacle_y[i]] != '.') continue;//拌马脚 
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[nx][ny] != '.') {
                    bool cur_color = (board[nx][ny] >= 'A' && board[nx][ny] <= 'Z');
                    if (cur_color != color) {
                        MaMoves.push_back(cur_move);
                    }
                    continue;
                }
                MaMoves.push_back(cur_move);
            }
            for (int i = 0; i < MaMoves.size(); i++) {
                if(color) {
                    MaMoves[i].score = MaPosition[MaMoves[i].next_y][9-MaMoves[i].next_x] - MaPosition[y][9-x];
                    red_moves.push_back(MaMoves[i]);
                }
                else {
                    MaMoves[i].score = MaPosition[MaMoves[i].next_y][MaMoves[i].next_x] - MaPosition[y][x];
                    black_moves.push_back(MaMoves[i]);
                }
            }
        }
        //生成炮的合法动作
        void generatePaoMoves(int x, int y, bool color) {
            //和车生成动作相似，需要考虑炮翻山吃子的情况
            std::vector<Move> PaoMoves;
            //TODO
            bool first_node = true; // 碰到第一颗棋子
            for(int i = x + 1; i < sizeX; i++) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                bool cur_color = (board[i][y] >= 'A' && board[i][y] <= 'Z');
                if(board[i][y] == '.' && first_node)
                {   // 如果没有棋子且没有碰到第一颗棋子
                    PaoMoves.push_back(cur_move);
                }
                else if (board[i][y] != '.' && first_node)
				{   // 如果有棋子且是碰到的第一颗棋子
                    first_node = false;
				}
                else if (board[i][y] == '.' && !first_node)
                {   // 如过没有棋子，且碰到过第一颗棋子
                    continue;
                }
                else if (board[i][y] != '.' && !first_node && cur_color != color) 
                {   // 如果有棋子且是碰到的第二颗棋子，且是对方的棋子
                    PaoMoves.push_back(cur_move);
                    break;
                }
                else if (board[i][y] != '.' && !first_node && cur_color == color)
                {   // 如果有棋子且碰到的是第二颗棋子，且是自己的棋子
                    break;
                }
            }
            
            
			// 其他方向的遍历
			first_node = true;
            for(int i = x - 1; i >= 0; i--) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                bool cur_color = (board[i][y] >= 'A' && board[i][y] <= 'Z');
                if(board[i][y] == '.')
                {   // 如果没有棋子
                    PaoMoves.push_back(cur_move);
                }
                else if (first_node)
				{   // 如果有棋子且是碰到的第一颗棋子
                    first_node = false;
				}
                else if (!first_node && board[i][y] != '.' && cur_color != color) 
                {   // 如果有棋子且是碰到的第二颗棋子，且是对方的棋子
                    PaoMoves.push_back(cur_move);
                    break;
                }
                else if(cur_color == color)
                {   // 如果有棋子且碰到的是第二颗棋子，且是自己的棋子
                    // 这里不置false，因为自己的棋子已经挡住后面的棋子，这一步无法走出
                    break;
                }
            }
            		
			first_node = true;
            for(int j = y + 1; j < sizeY; j++) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = x;
                cur_move.next_y = j;
                cur_move.score = 0;
                bool cur_color = (board[x][j] >= 'A' && board[x][j] <= 'Z');
                if(board[x][j] == '.')
                {   // 如果没有棋子
                    PaoMoves.push_back(cur_move);
                }
                else if (first_node)
				{   // 如果有棋子且是碰到的第一颗棋子
                    first_node = false;
				}
                else if (!first_node && board[x][j] != '.' && cur_color != color) 
                {   // 如果有棋子且是碰到的第二颗棋子，且是对方的棋子
                    PaoMoves.push_back(cur_move);
                    break;
                }
                else if(cur_color == color)
                {   // 如果有棋子且碰到的是第二颗棋子，且是自己的棋子
                    // 这里不置false，因为自己的棋子已经挡住后面的棋子，这一步无法走出
                    break;
                }
            }
            
            first_node = true;
            for(int j = y - 1; j >= 0; j--) {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = x;
                cur_move.next_y = j;
                cur_move.score = 0;
                bool cur_color = (board[x][j] >= 'A' && board[x][j] <= 'Z');
                if(board[x][j] == '.')
                {   // 如果没有棋子
                    PaoMoves.push_back(cur_move);
                }
                else if (first_node)
				{   // 如果有棋子且是碰到的第一颗棋子
                    first_node = false;
				}
                else if (!first_node && board[x][j] != '.' && cur_color != color) 
                {   // 如果有棋子且是碰到的第二颗棋子，且是对方的棋子
                    PaoMoves.push_back(cur_move);
                    break;
                }
                else if(cur_color == color)
                {   // 如果有棋子且碰到的是第二颗棋子，且是自己的棋子
                    // 这里不置false，因为自己的棋子已经挡住后面的棋子，这一步无法走出
                    break;
                }
            }

            
            for (int i = 0; i < PaoMoves.size(); i++) {
                if(color) {
                    PaoMoves[i].score = PaoPosition[PaoMoves[i].next_y][9 - PaoMoves[i].next_x] - PaoPosition[y][9 -x];
                    red_moves.push_back(PaoMoves[i]);
                }
                else {
                    PaoMoves[i].score = PaoPosition[PaoMoves[i].next_y][PaoMoves[i].next_x] - PaoPosition[y][x];
                    black_moves.push_back(PaoMoves[i]);
                }
            }
        }
        

        //生成相的合法动作
        void generateXiangMoves(int x, int y, bool color) {
            std::vector<Move> XiangMoves;
            //TODO
			int dx[] = {2, -2, -2, 2};
            int dy[] = {2, 2, -2, -2};
            int obstacle_x[] = {1, -1, -1, 1};
            int obstacle_y[] = {1, 1, -1, -1};
            for(int i = 0; i < 4; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (color)
                {
                	if (nx < 5 || nx >= 10 || ny < 0 || ny >= 9) continue;
                }
                else
                {
                	if (nx < 0 || nx >= 5 || ny < 0 || ny >= 9) continue;
                }
                if (board[x + obstacle_x[i]][y + obstacle_y[i]] != '.') continue; 
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[nx][ny] != '.') {
                    bool cur_color = (board[nx][ny] >= 'A' && board[nx][ny] <= 'Z');
                    if (cur_color != color) {
                        XiangMoves.push_back(cur_move);
                    }
                    continue;
                }
                XiangMoves.push_back(cur_move);
            }

            for (int i = 0; i < XiangMoves.size(); i++) {
                if(color) {
                    XiangMoves[i].score = XiangPosition[XiangMoves[i].next_y][9 - XiangMoves[i].next_x] - XiangPosition[y][9 -x];
                    red_moves.push_back(XiangMoves[i]);
                }
                else {
                    XiangMoves[i].score = XiangPosition[XiangMoves[i].next_y][XiangMoves[i].next_x] - XiangPosition[y][x];
                    black_moves.push_back(XiangMoves[i]);
                }
            }
        }

        //生成士的合法动作
        void generateShiMoves(int x, int y, bool color) {
            std::vector<Move> ShiMoves;
            //TODO
			int dx[] = {1, -1, -1, 1};
            int dy[] = {1, 1, -1, -1};
            for(int i = 0; i < 4; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (color)
                {
                	if (nx < 7 || nx >= 10 || ny < 3 || ny >= 6) continue;
                }
                else
                {
                	if (nx < 0 || nx >= 3 || ny < 3 || ny >= 6) continue;
                }
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[nx][ny] != '.') {
                    bool cur_color = (board[nx][ny] >= 'A' && board[nx][ny] <= 'Z');
                    if (cur_color != color) {
                        ShiMoves.push_back(cur_move);
                    }
                    continue;
                }
                ShiMoves.push_back(cur_move);
            }

            for (int i = 0; i < ShiMoves.size(); i++) {
                if(color) {
                    ShiMoves[i].score = ShiPosition[ShiMoves[i].next_y][9 - ShiMoves[i].next_x] - ShiPosition[y][9 -x];
                    red_moves.push_back(ShiMoves[i]);
                }
                else {
                    ShiMoves[i].score = ShiPosition[ShiMoves[i].next_y][ShiMoves[i].next_x] - ShiPosition[y][x];
                    black_moves.push_back(ShiMoves[i]);
                }
            }
        }

        //生成将的合法动作
        void generateJiangMoves(int x, int y, bool color) {
            std::vector<Move> JiangMoves;
            //TODO
            // 优先级最高的是对将
            for(int i = x + 1; i < sizeX; i++)
            {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                if(board[i][y] != '.' && board[i][y] != 'K')
                {
                    break;
                }
                if(board[i][y] == 'K')
                {   // 如果是对将
                    JiangMoves.push_back(cur_move);
                    break;
                }
            }
            for(int i = x - 1; i >= 0; i--)
            {
                Move cur_move;
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = i;
                cur_move.next_y = y;
                cur_move.score = 0;
                if(board[i][y] != '.' && board[i][y] != 'k')
                {
                    break;
                }
                if(board[i][y] == 'k')
                {   // 如果是对将
                    JiangMoves.push_back(cur_move);
                    break;
                }
            }   
            
            
            // 正常走法
			int dx[] = {0, -1, 0, 1};
            int dy[] = {1, 0, -1, 0};
            for(int i = 0; i < 4; i++) {
                Move cur_move;
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (color)
                {
                	if (nx < 7 || nx >= 10 || ny < 3 || ny >= 6) continue;
                }
                else
                {
                	if (nx < 0 || nx >= 3 || ny < 3 || ny >= 6) continue;
                }	
                cur_move.init_x = x;
                cur_move.init_y = y;
                cur_move.next_x = nx;
                cur_move.next_y = ny;
                cur_move.score = 0;
                if (board[nx][ny] != '.') {
                    bool cur_color = (board[nx][ny] >= 'A' && board[nx][ny] <= 'Z');
                    if (cur_color != color) {
                        JiangMoves.push_back(cur_move);
                    }
                    continue;
                }
                JiangMoves.push_back(cur_move);
            }

            for (int i = 0; i < JiangMoves.size(); i++) {
                if(color) {
                    JiangMoves[i].score = JiangPosition[JiangMoves[i].next_y][9 - JiangMoves[i].next_x] - JiangPosition[y][9 -x];
                    red_moves.push_back(JiangMoves[i]);
                }
                else {
                    JiangMoves[i].score = JiangPosition[JiangMoves[i].next_y][JiangMoves[i].next_x] - JiangPosition[y][x];
                    black_moves.push_back(JiangMoves[i]);
                }
            }
        }

        //生成兵的合法动作
        void generateBingMoves(int x, int y, bool color) {
            //需要分条件考虑，小兵在过楚河汉界之前只能前进，之后可以左右前
            std::vector<Move> BingMoves;
            //TODO
            if(color)
            {
                if(x >= 5)
                {
                    Move cur_move;
                    int nx = x - 1;
                    int ny = y;
                    // 在过河之前只能前进，不会越界，不考虑越界情况
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = nx;
                    cur_move.next_y = ny;
                    cur_move.score = 0;
                    if(board[nx][ny] != '.') {
                        bool cur_color = (board[nx][ny] >= 'A' && board[nx][ny] <= 'Z');
                        if(cur_color != color) {
                            BingMoves.push_back(cur_move);
                        }
                    }
                    else BingMoves.push_back(cur_move);
                }
                else if(x < 5 && x >= 0)
                {
                    int dx[] = {0, -1, 0};
                    int dy[] = {1, 0, -1};
                    for(int i = 0; i < 3; i++)
                    {
                        Move cur_move;
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (ny < 0 || ny >= 9 || nx < 0) continue; // 不会后退所以不考虑x过大的越界
                        cur_move.init_x = x;
                        cur_move.init_y = y;
                        cur_move.next_x = nx;
                        cur_move.next_y = ny;
                        cur_move.score = 0;
                        if(board[nx][ny] != '.') {
                            bool cur_color = (board[nx][ny] >= 'A' && board[nx][ny] <= 'Z');
                            if(cur_color != color) {
                                BingMoves.push_back(cur_move);
                            }
                            continue;
                        }
                        else BingMoves.push_back(cur_move);
                    }
                }
            }
            else
            {
                if(x < 5)
                {
                    Move cur_move;
                    int nx = x + 1;
                    int ny = y;
                    // 在过河之前只能前进，不会越界，不考虑越界情况
                    cur_move.init_x = x;
                    cur_move.init_y = y;
                    cur_move.next_x = nx;
                    cur_move.next_y = ny;
                    cur_move.score = 0;
                    if(board[nx][ny] != '.') {
                        bool cur_color = (board[nx][ny] >= 'A' && board[nx][ny] <= 'Z');
                        if(cur_color != color) {
                            BingMoves.push_back(cur_move);
                        }
                    }
                    else BingMoves.push_back(cur_move);
                }
                else if(x >= 5 && x < 10)
                {
                    int dx[] = {0, 1, 0};
                    int dy[] = {1, 0, -1};
                    for(int i = 0; i < 3; i++)
                    {
                        Move cur_move;
                        int nx = x + dx[i];
                        int ny = y + dy[i];
                        if (ny < 0 || ny >= 9 || nx >= 10) continue; // 不会后退所以不考虑x小的越界
                        cur_move.init_x = x;
                        cur_move.init_y = y;
                        cur_move.next_x = nx;
                        cur_move.next_y = ny;
                        cur_move.score = 0;
                        if(board[nx][ny] != '.') {
                            bool cur_color = (board[nx][ny] >= 'A' && board[nx][ny] <= 'Z');
                            if(cur_color != color) {
                                BingMoves.push_back(cur_move);
                            }
                            continue;
                        }
                        else BingMoves.push_back(cur_move);
                    }
                }
            }

            for (int i = 0; i < BingMoves.size(); i++) {
                if(color) {
                    BingMoves[i].score = BingPosition[BingMoves[i].next_y][9 - BingMoves[i].next_x] - BingPosition[y][9 -x];
                    red_moves.push_back(BingMoves[i]);
                }
                else {
                    BingMoves[i].score = BingPosition[BingMoves[i].next_y][BingMoves[i].next_x] - BingPosition[y][x];
                    black_moves.push_back(BingMoves[i]);
                }
            }
        }
    
        //终止判断
        bool judgeTermination() {
            //TODO
            int kingnum = 0;
            for (int i=0;i<pieces.size();i++)
            {
            	if (pieces[i].name == 'k' || pieces[i].name == 'K') kingnum++;
			}
            return (kingnum != 2);
        }

        //棋盘分数评估，根据当前棋盘进行棋子价值和棋力评估，max玩家减去min玩家分数
        int evaluateNode() {
            //TODO
            int maxscore,minscore;
            maxscore = 0;
            minscore = 0;
            for (int i=0;i<pieces.size();i++)
            {
            	char pieceChar = pieces[i].name;
            	switch (pieceChar) {
                        case 'R':
                            maxscore += piece_values["Ju"] + JuPosition[pieces[i].init_y][9-pieces[i].init_x];
                            break;
                        case 'C':
                            maxscore += piece_values["Pao"] + PaoPosition[pieces[i].init_y][9-pieces[i].init_x];
                            break;
                        case 'N':
                            maxscore += piece_values["Ma"] + MaPosition[pieces[i].init_y][9-pieces[i].init_x];
                            break;
                        case 'B':
                            maxscore += piece_values["Xiang"] + XiangPosition[pieces[i].init_y][9-pieces[i].init_x];
                            break;
                        case 'A':
                            maxscore += piece_values["Shi"] + ShiPosition[pieces[i].init_y][9-pieces[i].init_x];
                            break;
                        case 'K':
                            maxscore += piece_values["Jiang"] + JiangPosition[pieces[i].init_y][9-pieces[i].init_x];
                            break;
                        case 'P':
                            maxscore += piece_values["Bing"] + BingPosition[pieces[i].init_y][9-pieces[i].init_x];
                            break;
                        case 'r':
                            minscore += piece_values["Ju"] + JuPosition[pieces[i].init_y][pieces[i].init_x];
                            break;
                        case 'c':
                            minscore += piece_values["Pao"] + PaoPosition[pieces[i].init_y][pieces[i].init_x];
                            break;
                        case 'n':
                            minscore += piece_values["Ma"] + MaPosition[pieces[i].init_y][pieces[i].init_x];
                            break;
                        case 'b':
                            minscore += piece_values["Xiang"] + XiangPosition[pieces[i].init_y][pieces[i].init_x];
                            break;
                        case 'a':
                            minscore += piece_values["Shi"] + ShiPosition[pieces[i].init_y][pieces[i].init_x];
                            break;
                        case 'k':
                            minscore += piece_values["Jiang"] + JiangPosition[pieces[i].init_y][pieces[i].init_x];
                            break;
                        case 'p':
                            minscore += piece_values["Bing"] + BingPosition[pieces[i].init_y][pieces[i].init_x];
                            break;
                        default:
                            break;
                    }
			}
			for (int i = 0; i < red_moves.size(); i++)
			{
				switch (board[red_moves[i].next_x][red_moves[i].next_y]) {
                        case 'r':
                            maxscore += next_move_values["Ju"];
                            break;
                        case 'c':
                            maxscore += next_move_values["Pao"];
                            break;
                        case 'n':
                            maxscore += next_move_values["Ma"];
                            break;
                        case 'b':
                            maxscore += next_move_values["Xiang"];
                            break;
                        case 'a':
                            maxscore += next_move_values["Shi"];
                            break;
                        case 'k':
                            maxscore += next_move_values["Jiang"];
                            break;
                        case 'p':
                            maxscore += next_move_values["Bing"];
                            break;
                        default:
                            break;
                    }
			}
			for (int i=0;i<black_moves.size();i++)
			{
				switch (board[black_moves[i].next_x][black_moves[i].next_y]) {
                        case 'R':
                            minscore += next_move_values["Ju"];
                            break;
                        case 'C':
                            minscore += next_move_values["Pao"];
                            break;
                        case 'N':
                            minscore += next_move_values["Ma"];
                            break;
                        case 'B':
                            minscore += next_move_values["Xiang"];
                            break;
                        case 'A':
                            minscore += next_move_values["Shi"];
                            break;
                        case 'K':
                            minscore += next_move_values["Jiang"];
                            break;
                        case 'P':
                            minscore += next_move_values["Bing"];
                            break;
                        default:
                            break;
                    }
			}
            return maxscore - minscore;
        }

        //测试接口
        std::vector<Move> getMoves(bool color) {
            if(color) return red_moves;
            return black_moves;
        }
    
        std::vector<ChessPiece> getChessPiece() {
            return pieces;
        }
    
        std::vector<std::vector<char>> getBoard() {
            return board;
        }
    };

    // 定义博弈树节点类
    class GameTreeNode {
    private:
        bool color; // 当前玩家类型，true为红色方、false为黑色方
        ChessBoard board; // 当前棋盘状态
        std::vector<GameTreeNode*> children; // 子节点列表
        int evaluationScore; // 棋盘评估分数

    public:
        // 构造函数
        GameTreeNode(bool color, std::vector<std::vector<char>> initBoard, int evaluationScore)
            : color(color), evaluationScore(evaluationScore) {
            board.initializeBoard(initBoard);
            std::vector<Move> moves = board.getMoves(color);
            children.clear();
            std::vector<std::vector<char>> cur_board = board.getBoard();

            // 为合法动作创建子节点
            // for (int i = 0; i < moves.size(); i++) {
            //     GameTreeNode* child = updateBoard(cur_board, moves[i], color);
            //     children.push_back(child);
            // }
        }

        //根据当前棋盘和动作构建新棋盘（子节点）
        GameTreeNode* updateBoard(std::vector<std::vector<char>> cur_board, Move move, bool color) {
            //TODO
            cur_board[move.next_x][move.next_y] = cur_board[move.init_x][move.init_y];
            cur_board[move.init_x][move.init_y] = '.';
            GameTreeNode* test = new GameTreeNode(!color, cur_board, move.score);
            children.push_back(test);
            return test;
            
        }

        //返回节点评估分数
        int getEvaluationScore() {
            evaluationScore = board.evaluateNode();
            return evaluationScore;
        }

        //返回棋盘类
        ChessBoard getBoardClass() {
            return board;
        }
        
        ~GameTreeNode() {
            for (GameTreeNode* child : children) {
                delete child;
            }
        }
    };
}
