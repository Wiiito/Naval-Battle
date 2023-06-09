// Sprites
Vector2i getInitialPos(Sprite object) {
    Vector2i pos(object.getPosition().x - object.getOrigin().x * object.getScale().x, object.getPosition().y - object.getOrigin().y * object.getScale().y);
    return pos;
}

Vector2i getFinalPos(Sprite object) {
    Vector2i pos(object.getPosition().x - object.getOrigin().x * object.getScale().x + object.getLocalBounds().width * object.getScale().x, object.getPosition().y - object.getOrigin().y * object.getScale().y + object.getLocalBounds().height * object.getScale().y);
    return pos;
}

bool isClickBetween(Vector2i click, Sprite object) {
    Vector2i iniPos = getInitialPos(object);
    Vector2i finalPos = getFinalPos(object);
    if (click.x >= iniPos.x && click.y >= iniPos.y && click.x <= finalPos.x && click.y <= finalPos.y) {
        return true;
    }
    return false;
}

// Text
Vector2i getInitialPos(Text object) {
    Vector2i pos(object.getPosition().x - object.getOrigin().x * object.getScale().x, object.getPosition().y - object.getOrigin().y * object.getScale().y);
    return pos;
}

Vector2i getFinalPos(Text object) {
    Vector2i pos(object.getPosition().x - object.getOrigin().x * object.getScale().x + object.getLocalBounds().width * object.getScale().x, object.getPosition().y - object.getOrigin().y * object.getScale().y + object.getLocalBounds().height * object.getScale().y);
    return pos;
}

bool isClickBetween(Vector2i click, Text object) {
    Vector2i iniPos = getInitialPos(object);
    Vector2i finalPos = getFinalPos(object);
    if (click.x >= iniPos.x && click.y >= iniPos.y && click.x <= finalPos.x && click.y <= finalPos.y) {
        return true;
    }
    return false;
}

// Rectangle Shape
Vector2i getInitialPos(RectangleShape object) {
    Vector2i pos(object.getPosition().x - object.getOrigin().x * object.getScale().x, object.getPosition().y - object.getOrigin().y * object.getScale().y);
    return pos;
}

Vector2i getFinalPos(RectangleShape object) {
    Vector2i pos(object.getPosition().x - object.getOrigin().x * object.getScale().x + object.getLocalBounds().width * object.getScale().x, object.getPosition().y - object.getOrigin().y * object.getScale().y + object.getLocalBounds().height * object.getScale().y);
    return pos;
}

bool isClickBetween(Vector2i click, RectangleShape object) {
    Vector2i iniPos = getInitialPos(object);
    Vector2i finalPos = getFinalPos(object);
    if (click.x >= iniPos.x && click.y >= iniPos.y && click.x <= finalPos.x && click.y <= finalPos.y) {
        return true;
    }
    return false;
}