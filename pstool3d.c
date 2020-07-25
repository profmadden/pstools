#include "pstool.h"
#include <stdlib.h>
#include <math.h>


static ps_3d_perspective perspective;
static ps_3d_vector camera; //for single camera view only
static ps_3d_vector euler_angles; 

static ps_3d_obj* queue= (ps_3d_obj  *) 0x0;
static int queue_length = 0;

//vector operations

ps_3d_vector ps_3d_new_vector(float x,float y, float z)
{
	return (ps_3d_vector) { x, y, z };
}

ps_3d_vector ps_3d_add_vectors(ps_3d_vector first, ps_3d_vector second)
{
	return (ps_3d_vector) { first.x + second.x, first.y + second.y, first.z + second.z };
}

ps_3d_vector ps_3d_subtract_vectors(ps_3d_vector first, ps_3d_vector second)
{
	return (ps_3d_vector) { first.x - second.x, first.y - second.y, first.z - second.z };
}

ps_3d_vector ps_3d_scale_vector(ps_3d_vector first, float scale)
{
	return (ps_3d_vector) { first.x* scale, first.y* scale, first.z* scale };
}

//color operations

ps_3d_color ps_3d_new_color(float r, float g, float b)
{
	ps_3d_color color = (ps_3d_color)malloc(sizeof(float) * 3);
	color->r = r, color->g = g, color->b = b;
	return color;
}

//obj operations

int ps_3d_new_box(ps_3d_vector pos, ps_3d_vector size, float z_rotation, ps_3d_color color)
{
	ps_3d_obj* prev=(ps_3d_obj*) 0x0;
	if (queue) prev = queue; 
	queue = (ps_3d_obj*)malloc(sizeof(ps_3d_obj));
	queue->color = color, queue->pos = pos,queue->z_rotation = z_rotation, queue->size = size;
	queue_length++;
	if (prev) queue->next = prev;
	return 0;
}

//draw operations


int ps_3d_draw_rectangle(FILE* fp, ps_3d_vector corners[4],ps_3d_color color)
{
	ps_setcolor(fp, color->r, color->g, color->b);
	ps_3d_vector temp, projections[4];
	int i;

	for (i = 0; i < 4; i++)
	{
		if (perspective == single_camera)
		{
			temp = ps_3d_subtract_vectors(corners[i], camera);
			projections[i] = ps_3d_add_vectors(camera, ps_3d_scale_vector(temp, -(camera.z / temp.z)));
			temp = ps_3d_new_vector(tan(euler_angles.x) * corners[i].z, tan(euler_angles.y) * corners[i].z, corners[i].z / tan(euler_angles.x));
			projections[i] = ps_3d_add_vectors(projections[i],temp);
		}
		else if (perspective == isometric)
		{
			temp = ps_3d_new_vector(tan(euler_angles.x) * corners[i].z, tan(euler_angles.y)*corners[i].z, corners[i].z / tan(euler_angles.x));
			projections[i] = ps_3d_add_vectors(corners[i],temp);
		}
	}
	fprintf(fp, "newpath %f %f moveto ", projections[3].x, projections[3].y);
	for (i = 0; i < 4; i++)
	{
		fprintf(fp, "%f %f lineto ", projections[i].x, projections[i].y);
	}
	fprintf(fp, "gsave fill grestore stroke\n");
}

int ps_3d_draw_cube(FILE* fp, ps_3d_vector pos, ps_3d_vector size, float z_rotation, ps_3d_color color)
{
	float zcos = cos(z_rotation), zsin = sin(z_rotation);
	ps_3d_vector p0,p1,p2,p3,p4,p5,p6,p7;
	p0 = pos;
	p1 = ps_3d_new_vector
	(
		pos.x + size.x * zcos,
		pos.y,
		pos.z + size.z * zsin
	);
	p2 = ps_3d_new_vector
	(
		pos.x - size.x * zsin,
		pos.y,
		pos.z + size.z * zcos
	);
	p3 = ps_3d_new_vector
	(
		pos.x + size.x * zcos - size.x * zsin,
		pos.y,
		pos.z + size.z * zcos + size.z * zsin
	);
	p4 = ps_3d_new_vector
	(
		pos.x + size.x * zcos,
		pos.y + size.y,
		pos.z + size.z * zsin
	);
	p5 = ps_3d_new_vector
	(
		pos.x + size.x * zcos - size.x * zsin,
		pos.y + size.y,
		pos.z + size.z * zcos + size.z * zsin
	);
	p6 = ps_3d_new_vector
	(
		pos.x - size.x * zsin,
		pos.y + size.y,
		pos.z + size.z * zcos
	);
	p7 = ps_3d_new_vector
	(
		pos.x,
		pos.y+size.y,
		pos.z
	);

	color->r -= 0.1, color->g -= 0.1, color->b -= 0.1;
	ps_3d_vector cornersE[4] = { p7, p0, p2, p6 };
	ps_3d_draw_rectangle(fp, cornersE, color);
	color->r += 0.1, color->g += 0.1, color->b += 0.1;

	ps_3d_vector cornersA[4] = { p1, p0, p2, p3 };
	ps_3d_draw_rectangle(fp, cornersA, color);

	ps_3d_vector cornersB[4] = { p1, p3 ,p5 ,p4 };
	ps_3d_draw_rectangle(fp, cornersB, color);

	ps_3d_vector cornersC[4] = { p6, p5 ,p3, p2 };
	ps_3d_draw_rectangle(fp, cornersC, color);

	color->r += 0.15, color->g += 0.15, color->b += 0.15;
	ps_3d_vector cornersD[4] = { p7, p4, p5 ,p6 };
	ps_3d_draw_rectangle(fp, cornersD, color);
	color->r -= 0.15, color->g -= 0.15, color->b -= 0.15;

	color->r += 0.1, color->g += 0.1, color->b += 0.1;
	ps_3d_vector cornersF[4] = { p0, p1, p4, p7 };
	ps_3d_draw_rectangle(fp, cornersF, color);
	color->r -= 0.1, color->g -= 0.1, color->b -= 0.1;

	return 0;
}

ps_3d_obj* ps_3d_sort_queue(ps_3d_obj* head,int length)
{
	if (head == NULL || head->next == NULL) return head;
	if (length == 0) return NULL;
	if (length == 1)
	{
		head->next = NULL;
		return head;
	}
	int i;
	ps_3d_obj* cursor,*left,*right, *returnPtr,decoy;

	for (cursor = head, i = 0; i < length / 2; i++) cursor = cursor->next;
	left=ps_3d_sort_queue(head, i);
	right=ps_3d_sort_queue(cursor, length - i);

	returnPtr = &decoy;
	cursor = returnPtr;

	while (left || right)
	{
		if (left == NULL)
		{
			cursor->next = right;
			cursor = cursor->next;
			break;
		}
		else if (right == NULL)
		{
			cursor->next = left;
			cursor = cursor->next;
			break;
		}
		else if (right->pos.y > left->pos.y)
		{
			cursor->next = left;
			left = left->next;
			cursor = cursor->next;
			cursor->next = NULL;
		}
		else
		{
			cursor->next = right;
			right = right->next;
			cursor = cursor->next;
			cursor->next = NULL;
		}
	}
	return returnPtr->next;
}

int ps_3d_draw_scene(FILE* fp, ps_3d_vector camera_pos,ps_3d_perspective pers, ps_3d_vector angles)
{
	perspective = pers;
	euler_angles = angles;
	camera = camera_pos;
	queue = ps_3d_sort_queue(queue, queue_length);
	while (queue)
	{
		ps_3d_draw_cube(fp, queue->pos, queue->size, queue->z_rotation, queue->color);
		free(queue);
		queue = queue->next;
	}
	return 0;
}