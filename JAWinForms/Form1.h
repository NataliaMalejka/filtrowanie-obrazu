﻿#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cstdint>
#include <cstdint>

#include <thread>
#include <chrono>
#include <future>

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

// void f(int)
//void (*mojwskaznik)(int)

typedef void(__fastcall* FilterCFunc)(int, int, unsigned char*, unsigned char*, int);


namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;

#pragma pack(push, 1)
	struct BMPHeader
	{
		uint16_t file_type;
		uint32_t file_size;
		uint16_t reserved1;
		uint16_t reserved2;
		uint32_t offset_data;
	};

	struct DIBHeader
	{
		uint32_t dib_header_size;
		int32_t width;
		int32_t height;
		uint16_t planes;
		uint16_t bit_count;
		uint32_t compression;
		uint32_t image_size;
		int32_t x_pixels_per_meter;
		int32_t y_pixels_per_meter;
		uint32_t colors_used;
		uint32_t colors_important;
	};
#pragma pack(pop)

	struct Pixel
	{
		uint8_t blue;
		uint8_t green;
		uint8_t red;
	};

	extern "C" {
		// #include "CLibrary.h"
#include "AsmLibrary.h"
	}
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	protected:
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(133, 57);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Zastosuj";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(133, 136);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(516, 339);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &Form1::pictureBox1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(133, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(516, 20);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(296, 57);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(353, 20);
			this->textBox2->TabIndex = 3;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Checked = true;
			this->radioButton1->Location = System::Drawing::Point(133, 99);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(32, 17);
			this->radioButton1->TabIndex = 4;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"C";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(234, 99);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(45, 17);
			this->radioButton2->TabIndex = 5;
			this->radioButton2->Text = L"Asm";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(812, 519);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button1);
			this->Name = L"Form1";
			this->Text = L"Form1";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

		bool loadBMP(const std::string& file_path, BMPHeader& bmp_header, DIBHeader& dib_header, std::vector<Pixel>& pixels)
		{
			std::ifstream file(file_path, std::ios::binary);
			if (!file)
			{
				return false;
			}

			file.read(reinterpret_cast<char*>(&bmp_header), sizeof(BMPHeader));
			if (bmp_header.file_type != 0x4D42)
			{
				return false;
			}

			file.read(reinterpret_cast<char*>(&dib_header), sizeof(DIBHeader));
			if (dib_header.bit_count != 24)
			{
				return false;
			}

			file.seekg(bmp_header.offset_data, std::ios::beg);

			int row_stride = (dib_header.width * 3 + 3) & ~3;
			pixels.resize(dib_header.width * dib_header.height);

			for (int y = 0; y < dib_header.height; ++y)
			{
				for (int x = 0; x < dib_header.width; ++x)
				{
					Pixel pixel;
					file.read(reinterpret_cast<char*>(&pixel), sizeof(Pixel));
					int index = (dib_header.height - 1 - y) * dib_header.width + x;
					pixels[index] = pixel;
				}

				file.ignore(row_stride - dib_header.width * 3);
			}

			file.close();
			return true;
		}


#pragma endregion

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		constexpr int NUM_CHANNELS = 3;

		using namespace System::Runtime::InteropServices;
		using namespace System::Drawing;
		System::String^ managedString = textBox1->Text;


		// create Image object from file
		Bitmap^ image = gcnew Bitmap(managedString);

		// get image width and height
		const int width = image->Width;
		const int height = image->Height;

		textBox2->Text = "wymiary obrazka: " + width.ToString() + " x " + height.ToString();


		unsigned char* image_data = new unsigned char[width * height * NUM_CHANNELS];

		// copy image data to image_data array
		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				Color color = image->GetPixel(x, y);
				image_data[(y * width + x) * NUM_CHANNELS + 0] = color.R;
				image_data[(y * width + x) * NUM_CHANNELS + 1] = color.G;
				image_data[(y * width + x) * NUM_CHANNELS + 2] = color.B;
			}
		}

		unsigned char* new_image_data = new unsigned char[width * height * NUM_CHANNELS];


		// apply filter
		// filterC(width, height, image_data, new_image_data, 1);
		// filterAsm(width, height, image_data, new_image_data, 4);

		bool bibliotekaC = true;

		if (radioButton1->Checked)
		{
			HINSTANCE hDLL = LoadLibrary(L"CLibrary.dll");
			if (!hDLL)
			{
				textBox2->Text = "Nie udalo sie wczytaæ CLibrary.dll";
				return;
			}

			FilterCFunc filterC = (FilterCFunc)GetProcAddress(hDLL, "filterC");
			if (!filterC)
			{
				textBox2->Text = "Nie udalo sie wczytaæ funkcji filterC";
				return;
			}

			String^ str;
			for (int numThreads = 1; numThreads <= 64; numThreads *= 2)
			{
				auto start = std::chrono::high_resolution_clock::now();
				filterC(width, height, image_data, new_image_data, numThreads);
				auto end = std::chrono::high_resolution_clock::now();

				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

				str += numThreads.ToString() + ": " + duration.count().ToString() + "ms  ";
			}
			textBox2->Text = str;

			FreeLibrary(hDLL);
		}
		else // biblioteka ASM
		{
			String^ str;
			for (int numThreads = 1; numThreads <= 64; numThreads *= 2)
			{
				auto start = std::chrono::high_resolution_clock::now();

				const int STRIP_HEIGHT = height / numThreads;
				std::vector<std::thread> threads;

				for (int i = 0; i < 1; i++)
				{
					const int START_ROW = STRIP_HEIGHT * i;
					threads.push_back(std::thread(filterAsm, width, height, image_data, new_image_data, STRIP_HEIGHT, START_ROW));
					//filterAsm(width, height, image_data, new_image_data, STRIP_HEIGHT, START_ROW);
				}

				for (std::thread& t : threads)
				{
					t.join();
				}

				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
				str += numThreads.ToString() + ": " + duration.count().ToString() + "ms  ";
			}
			textBox2->Text = str;
		}



		Bitmap^ new_image = gcnew Bitmap(width, height);

		for (int y = 0; y < height; ++y)
		{
			for (int x = 0; x < width; ++x)
			{
				Color color = Color::FromArgb(
					new_image_data[(y * width + x) * NUM_CHANNELS + 0],
					new_image_data[(y * width + x) * NUM_CHANNELS + 1],
					new_image_data[(y * width + x) * NUM_CHANNELS + 2]);
				new_image->SetPixel(x, y, color);
			}
		}


		pictureBox1->SizeMode = PictureBoxSizeMode::Zoom;
		pictureBox1->Image = new_image;
	}

	private: System::Void pictureBox1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}