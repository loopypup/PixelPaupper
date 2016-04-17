void drawPlayer(Player * p, byte doClear)
{
  byte i, j;
  byte count = 0;
  static Color clearColor;
  
  for(i = p->x-2; i <= p->x + 2; i++)
  {
    for(j = p->y-2; j <= p->y + 2; j++)
    {
      //Serial.println(p->mask[i + j * 5]);
      if(p->mask[count])
      {
        if (doClear)
        {
          setPixel(i, j, clearColor);
        }
        else
        {
          setPixel(i, j, p->color);
        }
      }
      count++;
    }
  }
  if(p -> bulletList != NULL)
  {
    drawBullet(p -> bulletList);
  }
}

void drawPlayers(Player * p1, Player * p2)
{
  drawPlayer(p1, 1);
  drawPlayer(p2, 1);
  setBlendMode(ADD_BLEND);
  drawPlayer(p1, 0);
  drawPlayer(p2, 0);
  setBlendMode(NO_BLEND);
  setPixel(p1->x, p1->y, p1->coreColor);
  setPixel(p2->x, p2->y, p2->coreColor);
}

void drawBullet(Bullet * b)
{
  setPixel(b -> x.pixel, b -> y.pixel, b -> color);
  if ( b -> nextBullet != NULL)
  {
    drawBullet(b -> nextBullet);
  }
}

void updateBullet(Bullet * b)
{
  b -> x.subShort += b -> dX;
  b -> y.subShort += b -> dY;
  if(b -> x.pixel >= 15 || b -> x.pixel <= 0)
  {
    b -> dX *= -1;
  }
  if(b -> y.pixel >= 15 || b -> y.pixel <= 0)
  {
    b -> dY *= -1;
  }
  Serial.print(b->x.pixel);
  Serial.print(" ");
  Serial.print(b->y.pixel);
  Serial.print(" ");
  Serial.print(b->dX);
  Serial.print(" ");
  Serial.print(b->dY);
  Serial.print("\n");
}

void updatePlayer(Player * p)
{
  if(p -> bulletList)
  {
    updateBullet(p -> bulletList);
  }
}

void playerShootBullet(Player * p)
{
  Bullet b;
  Color c;
  c.longColor = 0x00101000;
  b.x.pixel = p->x;
  b.y.pixel = p->y;
  b.dY = -1;
  b.nextBullet = NULL;
  b.color = c;
  addBullet(&(p -> bulletList), &b);
}

void addBullet(Bullet ** bList, Bullet * b)
{
  while(*bList != NULL)
  {
    bList = &((*bList) -> nextBullet);
  }
  (*bList) = b;
}

void rotatePlayer(Player * p)
{
  byte i, j;
  byte tempArray[25]; 
  for(i = 0; i < 5; i++)
  {
    for(j = 0; j < 5; j++)
    {
      tempArray[j + (-i + 4) * 5]  = p->mask[i + j * 5];
    }
  }
  memcpy(p->mask, tempArray, 25);
}

void drawEnemy(Enemy * e)
{
  byte i, j;
  byte count = 0;
  
  for(j = e->y; j <= e->y + 3; j++)
  {
    for(i = e->x; i <= e->x + 3; i++)
    {
      if(e->mask[count])
      {
        setPixel(i, j, e->color);
      }
      count++;
    }
  }
  if(e -> bulletList != NULL)
  {
    drawBullet(e -> bulletList);
  }
}

