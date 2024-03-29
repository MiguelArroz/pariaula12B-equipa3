/** *     @file   auxcallbacks.c
 *     @brief  Auxiliary functions that are not callbacks but are used by them
 *
 *     Detailed description starts here.
 *
 *     @author  Vitor Santos, vitor@ua.pt
 *
 * =========================================================
 */

#define _AUXCALLBACKS_C_

#include "myf.h"

//--- Functions associated to the main callbacks for the drawing area ---//
//--- Students have to develop them in a team work ---//
// One of them is given as example : pari_draw_regularpolygon()

/**
 * @brief Draw a regular polygon
 * 
 * @param event 
 */
void pari_draw_regularpolygon(GdkEvent *event)
{
	static int last_button = 0;
	GdkEventButton *geb = (GdkEventButton *)event; //aux variable
	switch (event->type)
	{
	case GDK_BUTTON_PRESS: //it's a new one
		last_button = geb->button;
		if (geb->button == 1) //left button
		{
			double x = geb->x;
			double y = geb->y;
			p_polygon *npoly = (p_polygon *)malloc(sizeof(p_polygon));
			npoly->x = (double *)malloc((statusG.regularpolygon_vertices) * sizeof(double));
			npoly->y = (double *)malloc((statusG.regularpolygon_vertices) * sizeof(double));
			double ang = 2 * M_PI / statusG.regularpolygon_vertices;
			double radius = 20;
			for (int n = 0; n < statusG.regularpolygon_vertices; n++)
			{
				double x1 = x + radius * cos(n * ang);
				double y1 = y + radius * sin(n * ang);
				npoly->x[n] = x1;
				npoly->y[n] = y1;
			}
			npoly->num_points = statusG.regularpolygon_vertices; //to close the polygon
			npoly->x0 = x;
			npoly->y0 = y;
			npoly->line_color = 0;
			npoly->fill_color = statusG.regularpolygon_rgbcolor;

			pari_add_poly_to_main_drawing(npoly, pdG);
		}

		break;

	case GDK_MOTION_NOTIFY:       //mouse motion means modifying one just drawn
		if (last_button == 1) //if last pressed button was the right one (avoid motion from other buttons)
		{
			double x = geb->x;
			double y = geb->y;
			double x0 = pdG->polys[pdG->num_poly - 1]->x0;
			double y0 = pdG->polys[pdG->num_poly - 1]->y0;
			p_polygon *npoly = pdG->polys[pdG->num_poly - 1];
			double ang = 2 * M_PI / statusG.regularpolygon_vertices;
			double radius = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
			double angoff = atan2(y - y0, x - x0);
			for (int n = 0; n < statusG.regularpolygon_vertices; n++)
			{
				double x1 = x0 + radius * cos(n * ang + angoff);
				double y1 = y0 + radius * sin(n * ang + angoff);
				npoly->x[n] = x1;
				npoly->y[n] = y1;
			}
		}

		break;

	default:
		//Does nothing
		break;
	}
}

/**
 * @brief Draw a star polygon
 * 
 * @param event 
 */
void pari_draw_starpolygon(GdkEvent *event)
{
	//...
}

/**
 * @brief Draw a free hand polygon
 * 
 * @param event 
 */
void pari_draw_freehandpolygon(GdkEvent *event)
{

	p_polygon *npoly = (p_polygon *)malloc(sizeof(p_polygon));

	npoly->x = (double *)malloc((10) * sizeof(double));
	npoly->y = (double *)malloc((10) * sizeof(double));

	GdkEventButton *geb = (GdkEventButton *)event; //aux variable
	switch (event->type)
	{
	case GDK_BUTTON_PRESS: //it's a new one

		if (Clicks < 10) //left button
		{
			double x = geb->x;
			double y = geb->y;
			xcoords[Clicks] = x;
			ycoords[Clicks] = y;
			Clicks++;
		}

		if (Clicks == 10)
		{
			for (int i = 0; i < 10; i++)
			{
				npoly->x[i] = xcoords[i];
				npoly->y[i] = ycoords[i];
			}
			
			npoly->num_points = 10;
			npoly->line_color = -1;
			npoly->fill_color = statusG.freehandpolygon_rgbcolor;
			pari_add_poly_to_main_drawing(npoly, pdG);
			Clicks = 0;
			break;
		}

		break;
	default:
		//Does nothing
		break;
	}
}

/**
 * @brief Draw a circular crown
 * 
 * @param event 
 */
void pari_draw_circularcrown(GdkEvent *event)
{
	static int last_button = 0;
	GdkEventButton *geb = (GdkEventButton *)event; //aux variable
	switch (event->type)
	{
	case GDK_BUTTON_PRESS: //it's a new one
		last_button = geb->button;
		if (geb->button == 1) //left button
		{
			double radius = 20;
			double x = geb->x;
			double y = geb->y;
			p_crown *npoly = (p_crown *)malloc(sizeof(p_crown));
			npoly->radius = radius;
			npoly->thickness = statusG.circularcrown_thickness; //to close the polygon
			npoly->line_color = 0;
			npoly->fill_color = statusG.circularcrown_rgbcolor;
			npoly->x0 = x;
			npoly->y0 = y;
			pari_add_crown_to_main_drawing(npoly, pdG);
		}

		break;

	case GDK_MOTION_NOTIFY:       //mouse motion means modifying one just drawn
		if (last_button == 1) //if last pressed button was the right one (avoid motion from other buttons)
		{
			double x = geb->x;
			double y = geb->y;
			double x0 = pdG->crowns[pdG->num_crowns - 1]->x0;
			double y0 = pdG->crowns[pdG->num_crowns - 1]->y0;
			p_crown *npoly = pdG->crowns[pdG->num_crowns - 1];
			double radius = sqrt((x - x0) * (x - x0) + (y - y0) * (y - y0));
			npoly->radius = radius;
		}

		break;

	default:
		//Does nothing
		break;
	}
}

/**
 * @brief Draw the strings
 * 
 * @param event 
 */
void pari_draw_text(GdkEvent *event)
{
	//...
}
