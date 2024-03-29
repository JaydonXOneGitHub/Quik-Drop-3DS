#include "v3e.h"

class Ball
{
public:
    Vector2 position, scale;
    C2D_Image image;

    bool hasCollided = false;

    Rectangle GetColliderBox()
    {
        return Rectangle(
            Vector2(position.x + 5, position.y + 5), 
            Vector2(
                ((image.subtex->width - 10) * scale.x),
                ((image.subtex->height - 10) * scale.y)));
    }

    Ball(
        C2D_SpriteSheet sheet,
        int index = 0, 
        Vector2 pos = Vector2(), 
        Vector2 scale = Vector2(1,1))
        : position(pos), scale(scale)
    {
        image = C2D_SpriteSheetGetImage(sheet, index);
    }

    void Render()
    {
        C2D_DrawImageAt(image, position.x, position.y, 0, nullptr, scale.x, scale.y);
    }

    void Update()
    {
        if (position.y < 300)
        {
            position.y += 20;
        }
    }
};