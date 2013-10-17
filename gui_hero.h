#ifndef _DREAM_GUIHERO_
#define _DREAM_GUIHERO_

#include "gui_animation.h"

class GUIHero : public GUIAnimation {
public:
  GUIHero( const std::string directory_path, const Coordinate position, const GUI* father);

  void AddAnimation( const int action, const int direction, const bool is_loop);
  void EndAnimation();

  virtual void Render( const Coordinate position);

protected:
  int action_;
  std::string directory_path_;
  Texture texture_second_;//�������ݡ���������վ������
  int frame_second_;
  float frame_fill_second_;
};

#endif