#include "player.hpp"

Player::Player(float px, float py, float pw, float ph, RenderWindow* pWindow)
{
    pos.x = px;
    pos.y = py;
    scale.x = pw;
    scale.y = ph;

    sPos.x = 0;
    sPos.y = 0;
    sScale.x = 64;
    sScale.y = 64;

    fScale.x = sScale.x * scale.x;
    fScale.y = sScale.y * scale.y;

    window = pWindow;
}

Player::~Player()
{
    delete window;
    SDL_DestroyTexture(texture);
}

void Player::LoadTexture(SDL_Texture* pTexture)
{
    texture = pTexture;
}

void Player::Update()
{
    if (pos.y >= (450 - 69.0f))
    {
        isGrounded = true;
    }
    else
    {
        isGrounded = false;
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_RIGHT])
    {
        xVel = speed;
    }
    else if (state[SDL_SCANCODE_LEFT])
    {
        xVel = -speed;
    }
    else
    {
        xVel = 0.0f;
    }

    if (state[SDL_SCANCODE_SPACE] && keyJumped == false && isGrounded == true)
    {
        yVel = -jumpForce;
        keyJumped = true;
        isGrounded = false;
    }
    else if (!state[SDL_SCANCODE_SPACE])
    {
        keyJumped = false;
    }

    yVel += gravity;

    pos.x += xVel;
    pos.y += yVel;

    pos.x = Math::Clamp(0, 800 - 64.0f, pos.x);
    pos.y = Math::Clamp(0, 450 - 64.0f, pos.y);
}

void Player::Draw()
{
    SDL_Rect src;
    src.x = sPos.x;
    src.y = sPos.y;
    src.w = sScale.x;
    src.h = sScale.y;

    SDL_Rect dest;
    dest.x = pos.x;
    dest.y = pos.y;
    dest.w = sScale.x * scale.x;
    dest.h = sScale.y * scale.y;

    window->Draw(texture, src, dest);
}