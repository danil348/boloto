#include "GameObgects.h"

void GameObgect::updatePos(int x, int y)
{
    this->x = x;
    this->y = y;
}

void GameObgect::updatePos()
{
    stepsCount++;
    x = tmpx;
    y = tmpy;
}

bool GameObgect::get�ollision(GameObgect player)
{
    return (x == player.x && y == player.y);
}

bool GameObgect::getOverflight�ollision(GameObgect player)
{
    int value = abs(player.y - player.tmpy);

    if (player.x < player.tmpx && player.y == player.tmpy) {
        // �������
        value = abs(player.x - player.tmpx);
        for (int i = 0; i < value; i++) {
            if (player.x + i == x && player.y == y) {
                return 1;
            }
        }
    }
    else if (player.x > player.tmpx && player.y == player.tmpy) {
        // �����
        value = abs(player.x - player.tmpx);
        for (int i = 0; i < value; i++) {
            if (player.x - i == x && player.y == y) {
                return 1;
            }
        }
    }
    else if (player.y < player.tmpy && player.x == player.tmpx) {
        // ����
        value = abs(player.y - player.tmpy);
        for (int i = 0; i < value; i++) {
            if (player.y + i == y && player.x == x) {
                return 1;
            }
        }
    }
    else if (player.y > player.tmpy && player.x == player.tmpx) {
        // �����
        value = abs(player.y - player.tmpy);
        for (int i = 0; i < value; i++) {
            if (player.y - i == y && player.x == x) {
                return 1;
            }
        }
    }
    return false;
}

bool GameObgect::getDiagonalOverflight�ollision(GameObgect player)
{
    int value = abs(player.x - player.tmpx);
    if (player.x < player.tmpx) {
        if (player.y < player.tmpy) {
            // ������� � ����
            for (int i = 0; i < value; i++) {
                if (player.x + i == x && player.y + i == y) {
                    return 1;
                }
            }
        }
        else {
            // ������� � �����
            for (int i = 0; i < value; i++) {
                if (player.x + i == x && player.y - i == y) {
                    return 1;
                }
            }
        }
    }
    else {
        if (player.y < player.tmpy) {
            // ������ � ����
            for (int i = 0; i < value; i++) {
                if (player.x - i == x && player.y + i == y) {
                    return 1;
                }
            }
        }
        else {
            // ������ � �����
            for (int i = 0; i < value; i++) {
                if (player.x - i == x && player.y - i == y) {
                    return 1;
                }
            }
        }
    }
    return false;
}

void GameObgect::walk(int row, int col, Settings settings)
{
    tmpx = x;
    tmpy = y;
    bool flag = true;

    do
    {
        flag = true;

        do
        {
            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
            if (x + tmpValueX < col && x + tmpValueX >= 0) {
                x += tmpValueX;
                flag = false;
            }
        } while (flag);

        flag = true;

        do
        {
            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
            if (y + tmpValueY < row && y + tmpValueY >= 0) {
                y += tmpValueY;
                flag = false;
            }
        } while (flag);
    } while (tmpValueX == 0 && tmpValueY == 0);


    tmpValueX = 0;
    tmpValueY = 0;
}

void GameObgect::intellectWalk(int row, int col, Settings settings, Highground Highground, GameObgect player)
{
    int playerX = !(player.tmpx < col / 2);
    int playerY = !(player.tmpy < row / 2);
    int mosquitoX = !(x < col / 2);
    int mosquitoY = !(y < row / 2);

    do
    {
        if (playerX == mosquitoX && playerY == mosquitoY) {
            if (playerX == 0 && playerY == 0) {
                // ����� ����� ������
                if (x > y) {
                    // ������ ����� ������� 
                    tmpx = x;
                    tmpy = y;
                    do
                    {
                        if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while (tmpValueX == 0 && tmpValueY == 0);
                        }
                        else if (y == 0 || y == row - 1) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                        }
                        else if (x == 0 || x == col - 1) {
                            do
                            {
                                tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                        }
                        else {
                            do
                            {
                                tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                        }
                    } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                    x += tmpValueX;
                    y += tmpValueY;
                }
                else {
                    // ������ ����� ����

                    tmpx = x;
                    tmpy = y;
                    do
                    {
                        if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while (tmpValueX == 0 && tmpValueY == 0);
                        }
                        else if (y == 0 || y == row - 1) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                        }
                        else if (x == 0 || x == col - 1) {
                            do
                            {
                                tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                        }
                        else {
                            do
                            {
                                tmpValueX = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                        }
                    } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                    x += tmpValueX;
                    y += tmpValueY;
                }

            }
            else if (playerX == 0 && playerY == 1) {
                // ����� ����� ����� 
                if (x > row - y) {
                    // ������ ���� �������
                    tmpx = x;
                    tmpy = y;
                    do
                    {
                        if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while (tmpValueX == 0 && tmpValueY == 0);
                        }
                        else if (y == 0 || y == row - 1) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                        }
                        else if (x == 0 || x == col - 1) {
                            do
                            {
                                tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                        }
                        else {
                            do
                            {
                                tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                        }
                    } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                    x += tmpValueX;
                    y += tmpValueY;
                }
                else {
                    // ������ ���� �����
                    tmpx = x;
                    tmpy = y;
                    do
                    {
                        if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while (tmpValueX == 0 && tmpValueY == 0);
                        }
                        else if (y == 0 || y == row - 1) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                        }
                        else if (x == 0 || x == col - 1) {
                            do
                            {
                                tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y);
                        }
                        else {
                            do
                            {
                                tmpValueX = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y );
                        }
                    } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                    x += tmpValueX;
                    y += tmpValueY;
                }
            }
            else if (playerX == 1 && playerY == 0) {
                // ����� ������ ������
                if (col - x > y) {
                    // ������ ���� ������
                    tmpx = x;
                    tmpy = y;
                    do
                    {
                        if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while (tmpValueX == 0 && tmpValueY == 0);
                        }
                        else if (y == 0 || y == row - 1) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                        }
                        else if (x == 0 || x == col - 1) {
                            do
                            {
                                tmpValueX = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = 0;
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX >= x);
                        }
                        else {
                            do
                            {
                                tmpValueX = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX >= x);
                        }
                    } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                    x += tmpValueX;
                    y += tmpValueY;
                }
                else {
                    // ������ ���� ����
                    tmpx = x;
                    tmpy = y;
                    do
                    {
                        if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            } while (tmpValueX == 0 && tmpValueY == 0);
                        }
                        else if (y == 0 || y == row - 1) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                        }
                        else if (x == 0 || x == col - 1) {
                            do
                            {
                                tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                        }
                        else {
                            do
                            {
                                tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                        }
                    } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                    x += tmpValueX;
                    y += tmpValueY;
                }
            }
            else {
                // ����� ������ �����
                if (col - x > row - y) {
                    // ������ ���� �����

                    tmpx = x;
                    tmpy = y;
                    do
                    {
                        if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                            do
                            {
                                tmpValueX = 0;
                                tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while (tmpValueX == 0 && tmpValueY == 0);
                        }
                        else if (y == 0 || y == row - 1) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                        }
                        else if (x == 0 || x == col - 1) {
                            do
                            {
                                tmpValueX = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX >= x);
                        }
                        else {
                            do
                            {
                                tmpValueX = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x+tmpValueX >= x);
                        }
                    } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                    x += tmpValueX;
                    y += tmpValueY;
                }
                else {
                    // ������ ���� �����

                    tmpx = x;
                    tmpy = y;
                    do
                    {
                        if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                            do
                            {
                                tmpValueX = 0;
                                tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while (tmpValueX == 0 && tmpValueY == 0);
                        }
                        else if (y == 0 || y == row - 1) {
                            do
                            {
                                tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                                tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                        }
                        else if (x == 0 || x == col - 1) {
                            do
                            {
                                tmpValueX = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y);
                        }
                        else {
                            do
                            {
                                tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                                tmpValueY = -abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y);
                        }
                    } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                    x += tmpValueX;
                    y += tmpValueY;

                }
            }
            //���� ����� ��������� � ����� ������ � �������
        }
        else if (playerX != mosquitoX && playerY == mosquitoY) {
            //���� ����� ��������� � ��� �� ������� �� y �� � ������ �� �
            if (playerX == 0 && playerY == 0) {
                // ����� ������ ������

                tmpx = x;
                tmpy = y;
                do
                {
                    if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                        do
                        {
                            tmpValueX = 0;
                            tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                        } while (tmpValueX == 0 && tmpValueY == 0);
                    }
                    else if (y == 0 || y == row - 1) {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                    }
                    else if (x == 0 || x == col - 1) {
                        do
                        {
                            tmpValueX = 0;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                    }
                    else {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y || x + tmpValueX <= x);
                    }
                } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                x += tmpValueX;
                y += tmpValueY;
            }
            else if (playerX == 1 && playerY == 0) {
                // ����� ����� ������
                tmpx = x;
                tmpy = y;
                do
                {
                    if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                        do
                        {
                            tmpValueX = 0;
                            tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                        } while (tmpValueX == 0 && tmpValueY == 0);
                    }
                    else if (y == 0 || y == row - 1) {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX >= x);
                    }
                    else if (x == 0 || x == col - 1) {
                        do
                        {
                            tmpValueX = 0;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                    }
                    else {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y || x + tmpValueX >= x);
                    }
                } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);

                x += tmpValueX;
                y += tmpValueY;
            }
            else if (playerX == 0 && playerY == 1) {
                // ����� ������ �����
                tmpx = x;
                tmpy = y;
                do
                {
                    if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                        do
                        {
                            tmpValueX = 0;
                            tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                        } while (tmpValueX == 0 && tmpValueY == 0);
                    }
                    else if (y == 0 || y == row - 1) {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                    }
                    else if (x == 0 || x == col - 1) {
                        do
                        {
                            tmpValueX = 0;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y);
                    }
                    else {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y || x + tmpValueX <= x);
                    }
                } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                x += tmpValueX;
                y += tmpValueY;
            }
            else {
                // ����� ����� �����
                tmpx = x;
                tmpy = y;
                do
                {
                    if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                        do
                        {
                            tmpValueX = 0;
                            tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                        } while (tmpValueX == 0 && tmpValueY == 0);
                    }
                    else if (y == 0 || y == row - 1) {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX >= x);
                    }
                    else if (x == 0 || x == col) {
                        do
                        {
                            tmpValueX = 0;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y);
                    }
                    else {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y || x + tmpValueX >= x);
                    }
                } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                x += tmpValueX;
                y += tmpValueY;
            }
        }
        else if (playerX == mosquitoX && playerY != mosquitoY) {
            //���� ����� ��������� � ��� �� ������� �� x �� � ������ �� y
            if (playerX == 0 && playerY == 0) {
                // ����� ����� �����
                tmpx = x;
                tmpy = y;
                do
                {
                    if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                        do
                        {
                            tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            tmpValueY = 0;
                        } while (tmpValueX == 0 && tmpValueY == 0);
                    }
                    else if (y == 0 || y == row - 1) {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = 0;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                    }
                    else if (x == 0 || x == col - 1) {
                        do
                        {
                            tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                    }
                    else {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x || y + tmpValueY <= y);
                    }
                } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);
                x += tmpValueX;
                y += tmpValueY;
            }
            else if (playerX == 1 && playerY == 0) {
                // ����� ������ �����
                tmpx = x;
                tmpy = y;
                do
                {
                    if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                        do
                        {
                            tmpValueX = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            tmpValueY = 0;
                        } while (tmpValueX == 0 && tmpValueY == 0);
                    }
                    else if (y == 0 || y == row - 1) {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = 0;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX >= x);
                    }
                    else if (x == 0 || x == col - 1) {
                        do
                        {
                            tmpValueX = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY <= y);
                    }
                    else {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX >= x || y + tmpValueY <= y);
                    }
                } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);

                x += tmpValueX;
                y += tmpValueY;
            }
            else if (playerX == 0 && playerY == 1) {
                // ����� ����� ������ +++++++++
                tmpx = x;
                tmpy = y;
                do
                {
                    if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                        do
                        {
                            tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            tmpValueY = 0;
                        } while (tmpValueX == 0 && tmpValueY == 0);
                    }
                    else if (y == 0 || y == row - 1) {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = 0;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX <= x);
                    }
                    else if (x == 0 || x == col - 1) {
                        do
                        {
                            tmpValueX = abs(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y);
                    }
                    else {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y || x + tmpValueX <= x);
                    }
                } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);

                x += tmpValueX;
                y += tmpValueY;
            }
            else {
                // ����� ������ ������ +++++++++
                tmpx = x;
                tmpy = y;
                do
                {
                    if ((x == 0 && y == 0) || (x == 0 && y == row - 1) || (x == col - 1 && y == 0) || (x == col - 1 && y == row - 1)) {
                        do
                        {
                            tmpValueX = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            tmpValueY = 0;
                        } while (tmpValueX == 0 && tmpValueY == 0);
                    }
                    else if (y == 0 || y == row - 1) {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX >= x);
                    }
                    else if (x == 0 || x == col - 1) {
                        do
                        {
                            tmpValueX = -(rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep);
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || y + tmpValueY >= y);
                    }
                    else {
                        do
                        {
                            tmpValueX = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                            tmpValueY = rand() % (settings.mosquitoCurrentStep * 2 + 1) - settings.mosquitoCurrentStep;
                        } while ((tmpValueX == 0 && tmpValueY == 0) || x + tmpValueX >= x || y + tmpValueY >= y);
                    }
                } while (x + tmpValueX >= col || x + tmpValueX < 0 || y + tmpValueY >= row || y + tmpValueY < 0);

                x += tmpValueX;
                y += tmpValueY;
            }
        }
        //else if()
        else {
            walk(row, col, settings);
        }
    } while (player.x == x + tmpValueX && player.y == y + tmpValueY);
}
