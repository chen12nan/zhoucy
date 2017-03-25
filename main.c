#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int m_id;  // 用来保存id
  int m_x;   // 保存x坐标
  int m_y;   // 保存y坐标

  struct Node *next;
} Point;

//全局变量， 用来指向链表的头
Point* g_head = NULL;
int g_count = 0;

// 添加一个点到链表中
void append(Point* point)
{
  // 第一个添加， 此时g_head是NULL
  if(g_head == NULL)
  {
    g_head = point;
    return ;
  }

  Point *pre = NULL;
  Point *cur = g_head;
  
  while(cur)
  {
    if(point->m_id < cur->m_id)
    {
      if(pre == NULL)
      {
        point->next = g_head;
        g_head = point;
      }
      else
      {
        pre->next = point;
        point->next = cur;
      }
      g_count++;
      return;
    }
    pre = cur;
    cur = cur->next;
  }

  g_count++;
  pre->next = point;
}

// 暂时没有用到
Point* get(int id)
{
  Point* cur = g_head;
  while(cur)
  {
    if(cur->m_id == id)
    {
      return cur;
    }
    cur = cur->next;
  }
  return NULL;
}

// 暂时没有用
int delete(Point* point)
{
  Point* pre = NULL;
  Point* cur = g_head;
  while(cur)
  {
    if(cur->m_id == point->m_id)
    {
      if(pre == NULL)
      {
        g_head = cur->next;
      }
      else
      {
        pre->next = cur->next;
      }
      free(cur);
      g_count--;
      return 1;
    }
    pre = cur;
    cur = cur->next;
  }

  return 0;
}

// 用来输出链表的数据
void output()
{
  Point* cur = g_head;
  while(cur)
  {
    printf("id = %d\n", cur->m_id);
    printf(" x = %d\n", cur->m_x);
    printf(" y = %d\n", cur->m_y);
   
    printf("--------------------------\n");
    cur = cur->next;
  }
}

// 用来删除掉2014.txt文件的头两行
void removeHead(FILE* fp)
{
  int ch = fgetc(fp);
  int count = 0;
  while(ch != EOF)
  {
    if(ch == '\n')
      count++;
    if(count == 2)
      break;
    ch = fgetc(fp);
  }
}

// 从文件中读取数据，把一行数据都放在Point里，然后把Point放到链表中
void readDataFromText(const char* fileName)
{
  FILE* fp = fopen(fileName, "r");

  if(fp != NULL)
  {
    removeHead(fp);

    int id, x, y;
    while(!feof(fp))
    {
      int ret = fscanf(fp, "%d %d %d", &id, &x, &y);
      if(ret == 3)
      {
        Point* p1 = (Point*)malloc(sizeof(Point));
        p1->next = NULL;
        p1->m_id = id;
        p1->m_x = x;
        p1->m_y = y;
        append(p1);
      }
      fgetc(fp);
    }
  }
  fclose(fp);
}

// 把链表的内容写入文件中
void writeDataToText(const char* fileName)
{
  FILE* fp = fopen(fileName, "w");
  if(fp != NULL)
  {
    fprintf(fp, "name: %s      number: %s\n\n", "zhoucy", "10108326");
    fprintf(fp, "  点号:       X坐标          Y坐标  \n");

    Point *cur = g_head;
    while(cur)
    {
      fprintf(fp, "   %d          %d            %d  \n", cur->m_id, cur->m_x, cur->m_y);
      cur = cur->next;
    }
  }
  fclose(fp);
}

int main()
{
  readDataFromText("2014.txt");
  writeDataToText("write_sort.txt");

  return 0;
}
