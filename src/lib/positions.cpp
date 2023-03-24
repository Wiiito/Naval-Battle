Vector2i getInitialPos(Text object) {
    Vector2i pos(object.getPosition().x - object.getOrigin().x, object.getPosition().y - object.getOrigin().y);
    return pos;
}

Vector2i getFinalPos(Text object) {
    Vector2i pos(object.getPosition().x - object.getOrigin().x + object.getLocalBounds().width, object.getPosition().y - object.getOrigin().y + object.getLocalBounds().height);
    return pos;
}

bool isClickBetween(Vector2i click, Vector2i iniPos, Vector2i finalPos) {
    if (click.x >= iniPos.x && click.y >= iniPos.y && click.x <= finalPos.x && click.y <= finalPos.y) {
        return true;
    }
    return false;
}