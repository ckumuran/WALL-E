#include "search.h"
    int alpha,
    int beta
) {
    if (depth == 0)
        return evaluate(board);
    MoveList list;
    generate_moves(board, list);
    if (list.count == 0)
        return evaluate(board);
    int best = -INF;
    for (int i = 0; i < list.count; i++) {
        StateInfo st;
        if (!make_move(board, list.moves[i].move, st))
            continue;
        int score = -negamax(
            board,
            info,
            depth - 1,
            -beta,
            -alpha
        );
        unmake_move(board, list.moves[i].move, st);
        if (score > best)
            best = score;
        if (score > alpha)
            alpha = score;
        if (alpha >= beta)
            break;
    }
    return best;
}
Move search_position(Board& board, int depth) {
    SearchInfo info;
    info.depth = depth;
    MoveList list;
    generate_moves(board, list);
    Move bestMove = 0;
    int bestScore = -INF;
    for (int i = 0; i < list.count; i++) {
        StateInfo st;
        make_move(board, list.moves[i].move, st);
        int score = -negamax(
            board,
            info,
            depth - 1,
            -INF,
            INF
        );
       unmake_move(board, list.moves[i].move, st);
        if (score > bestScore) {
            bestScore = score;
            bestMove = list.moves[i].move;
        }
    }
    return bestMove;
}
