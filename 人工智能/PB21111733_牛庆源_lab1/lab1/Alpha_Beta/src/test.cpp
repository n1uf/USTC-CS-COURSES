#include <fstream>
#include "node.h"
#define MaxDepth 3

int step_nums = 0;

using namespace ChineseChess;

//博弈树搜索，depth为搜索深度
int alphaBeta(GameTreeNode node, int alpha, int beta, int depth, bool isMaximizer) {
    if (depth == 0) {
        return node.getEvaluationScore();
    }
    //TODO alpha-beta剪枝过程

	ChessBoard board = node.getBoardClass();
	std::vector<Move> moves = board.getMoves(isMaximizer);
	std::vector<std::vector<char>> cur_board = board.getBoard();

	int bestscore = 0;
	int bestmove = 0;
	if(isMaximizer)
	{
		bestscore = std::numeric_limits<int>::min();
		for(int i = 0; i < moves.size(); i++)
		{
			bool cur_color = cur_board[moves[i].init_x][moves[i].init_y] >= 'A' 
				&& cur_board[moves[i].init_x][moves[i].init_y] <= 'Z';
			if(cur_color != isMaximizer) continue;
			GameTreeNode *child = node.updateBoard(cur_board, moves[i], isMaximizer);
			if(child->getBoardClass().judgeTermination())
			{
				bestscore = std::numeric_limits<int>::max();
				bestmove = i;
				break;
			}
			int score = alphaBeta(*child, alpha, beta, depth - 1, !isMaximizer);
			alpha = std::max(alpha, score);
			bestscore = std::max(bestscore, score);
			if(bestscore == score) bestmove = i;
			if(alpha >= beta) break;
		}
	}
	else
	{
		bestscore = std::numeric_limits<int>::max();
		for(int i = 0; i < moves.size(); i++)
		{
			bool cur_color = cur_board[moves[i].init_x][moves[i].init_y] >= 'A' 
				&& cur_board[moves[i].init_x][moves[i].init_y] <= 'Z';
			if(cur_color != isMaximizer) continue;
			GameTreeNode *child = node.updateBoard(cur_board, moves[i], isMaximizer);
			if(child->getBoardClass().judgeTermination())
			{
				bestscore = std::numeric_limits<int>::min();
				break;
			}
			int score = alphaBeta(*child, alpha, beta, depth - 1, !isMaximizer);
			beta = std::min(beta, score);
			bestscore = std::min(bestscore, score);
			if(alpha >= beta) break;
		}
	}

	if(depth == MaxDepth)
	{	// 输出
		std::ofstream file("../output/output_"+std::to_string(step_nums)+".txt");
		if(file.is_open())
		{
			file<<cur_board[moves[bestmove].init_x][moves[bestmove].init_y]<<" ("
				<<moves[bestmove].init_y<<", "<<moves[bestmove].init_x<<") -> ("
				<<moves[bestmove].next_y<<", "<<moves[bestmove].next_x<<")";
			file.close();
		}
		else
		{
			std::cerr<<"Can not open file: "<<"../output/output_"+std::to_string(step_nums)+".txt"<<std::endl;
		}
	}	
    return bestscore;
}

int main() {
    for(step_nums = 1; step_nums < 11; step_nums ++)
    {
        std::ifstream file("../input/"+std::to_string(step_nums)+".txt");
        std::vector<std::vector<char>> board;

        std::string line;
        int n = 0;
        while (std::getline(file, line)) {
            std::vector<char> row;

            for (char ch : line) {
                row.push_back(ch);
            }

            board.push_back(row);
            n = n + 1;
            if (n >= 10) break;
        }

        file.close();
        GameTreeNode root(true, board, std::numeric_limits<int>::min());

        //TODO
        alphaBeta(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), MaxDepth, true);
	}


    //代码测试
    /*
    ChessBoard _board = root.getBoardClass();
    std::vector<std::vector<char>> cur_board = _board.getBoard();

    for (int i = 0; i < cur_board.size(); i++) {
        for (int j = 0; j < cur_board[0].size(); j++) {
            std::cout << cur_board[i][j];
        }
        std::cout << std::endl;
    }

    std::vector<Move> red_moves = _board.getMoves(true);
    std::vector<Move> black_moves = _board.getMoves(false);

    for (int i = 0; i < red_moves.size(); i++) {
        std::cout << "init: " << red_moves[i].init_x <<  " " << red_moves[i].init_y << std::endl;
        std::cout << "next: " << red_moves[i].next_x <<  " " << red_moves[i].next_y << std::endl;
        std::cout << "score " << red_moves[i].score << std::endl;
    }
    for (int i = 0; i < black_moves.size(); i++) {
        std::cout << "init: " << black_moves[i].init_x <<  " " << black_moves[i].init_y << std::endl;
        std::cout << "next: " << black_moves[i].next_x <<  " " << black_moves[i].next_y << std::endl;
        std::cout << "score " << black_moves[i].score << std::endl;
    }
    */
    return 0;
}