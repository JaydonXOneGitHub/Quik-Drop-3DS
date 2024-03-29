#include "v3e.h"

class Bucket
{
public:
    Vector2 position, scale;
    C2D_Image image;

    Rectangle GetColliderBox()
    {
        return Rectangle(
            Vector2(position.x + 13, position.y), 
            Vector2(
                (image.subtex->width * scale.x) - 26,
                (3 * scale.y)));
    }

    Bucket(
        C2D_SpriteSheet sheet,
        int index = 0, 
        float xPos = 0, 
        Vector2 scale = Vector2(1,1))
        : scale(scale)
    {
        image = C2D_SpriteSheetGetImage(sheet, index);
        position = Vector2(xPos,
            (240 - (image.subtex->height * scale.y)));
    }

    void Render()
    {
        C2D_DrawImageAt(image, position.x, position.y, 0, nullptr, scale.x, scale.y);
    }

    void Update()
    {
        if (position.x > 401)
        {
            position.x = -((image.subtex->width * scale.x) + 1);
        }

        position.x += 2;
    }
};