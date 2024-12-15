#define _USE_MATH_DEFINES
#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>

const float start = M_PI / 2;
const float end = 8 * M_PI;
const int steps = 300;

void drawLines(int, float, float, float, float);

void drawLines(int centerY, float scaleX, float scaleY, float maxY, float minY) {
	line(0, getmaxy(), getmaxx(), getmaxy()); // X scale
	line(0, 0, 0, getmaxx()); // Y scale

	// layout for scale X
	for (int i = 1; i <= 16; ++i) {
		int xCoord = int((M_PI * i) / scaleX);
		line(xCoord, getmaxy() - 5, xCoord, getmaxy() + 5); // marks

		// Output X values
		char labelX[10];
		sprintf(labelX, "%d pi", i);
		outtextxy(xCoord - 5, getmaxy() - 15, labelX);
	}
	// layout for scale Y
	float stepY = (maxY - minY) / 10;
	for (int j = 0; j <= 10; ++j) {
		// Find y coord
		int yCoord = centerY - int((minY + j * stepY) / scaleY);
		line(-5, yCoord, 5, yCoord); // Marks

		// Output Y values
		char labelY[10];
		sprintf(labelY, "%.2f", minY + j * stepY);
		outtextxy(10, yCoord - 5, labelY);
	}
}

void drawGraphic(float* X, float* Y, float scaleX, float scaleY, float centerY) {
	for (int k = 0; k < steps - 1; ++k) {
		int x1 = int(X[k] / scaleX);
		int y1 = centerY - int(Y[k] / scaleY);
		int x2 = int(X[k + 1] / scaleX);
		int y2 = centerY - int(Y[k + 1] / scaleY);
		line(x1, y1, x2, y2);
	}
}

int main() {
	clrscr();
	int graph_driver = DETECT, graph_mode, graph_error_code;
	initgraph(&graph_driver, &graph_mode, "C:\\YOGISOFT\\TC\\BGI\\EGAVGA.BGI");
	printf("GD = %d, GM = %d", graph_driver, graph_mode);
	graph_error_code = graphresult();
	if (graph_error_code != grOk) {
		return 255;
	}

	// Arrays for coords
	float X[steps];
	float Y[steps];
	float step = (end - start) / steps;

	// Append values to arrays
	X[0] = start;
	Y[0] = pow(sin(start), 3) - pow(cos(start), 2);

	for (int i = 1; i < steps; ++i) {
		X[i] = X[i - 1] + step;
		Y[i] = pow(sin(X[i]), 3) - pow(cos(X[i]), 2);
	}

	float maxY = Y[0], minY = Y[0];
	for (int j = 1; j < steps; ++j) {
		if (Y[j] > maxY) maxY = Y[j];
		if (Y[j] < minY) minY = Y[j];
	}

	float scaleX = end / getmaxx();
	float scaleY = (maxY - minY) / getmaxy();
	int centerY = getmaxy();
	drawLines(centerY, scaleX, scaleY, maxY, minY);
	drawGraphic(X, Y, scaleX, scaleY, centerY);
	char maxValueLabel[10];
	sprintf(maxValueLabel, "Max value: %.2f", maxY);
	outtextxy(500, 30, maxValueLabel);
	char funcView[10];
	sprintf(funcView, "y(x) = sin^3(x) - cos^2(x)");
	outtextxy(3, 3, funcView);
	getch();

	return 0;
}





















