#ifndef APP_UTIL_HPP
#define APP_UTIL_HPP

#include "pch.hpp" // IWYU pragma: export

namespace AppUtil {

/*
 * READY: 剛載入遊戲，顯示 "Get Ready"，等待玩家按下跳躍鍵開始。
 * PLAYING: 遊戲進行中，小鳥受重力影響，水管移動，計算碰撞與得分。
 * GAME_OVER: 玩家碰到障礙物死亡，顯示 "Game Over"，等待玩家重新開始。
 */
enum class Phase {
  READY,
  PLAYING,
  GAME_OVER,
};

} // namespace AppUtil

#endif // APP_UTIL_HPP
