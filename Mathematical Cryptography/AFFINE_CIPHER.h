#include "MAPS.h"

// global items used throughout these ciphers
vector<vector<char> > cipher, answer;
bool done = false;
ofstream fout;
int choice = -1, factor = 1, shift = 1;

vector<vector<char> > encryptAFFINE(vector<vector<char> > input, int a, int b) // returns encrypted 2-D char vector
{
	// encryption block. 
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[i].size(); j++)
		{
			if (isalpha(input[i][j])) // skips spaces and punctuation.
			{
				if (islower(input[i][j])) // converts to caps as needed. 
				{
					input[i][j] = toupper(input[i][j]);
				}
				input[i][j] = MOD26char[((MOD26int[input[i][j]] * a) + b) % 26]; // performs affine encryption
			}
		}
	}

	// display block. 
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[i].size(); j++)
		{
			cout << input[i][j];
		}
		puts("");
	}
	return input;
}

vector<vector<char> > decryptAFFINE(vector<vector<char> > input, int a, int b) // returns decrypted 2-D char vector
{
	// decryption block. 
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[i].size(); j++)
		{
			if (isalpha(input[i][j])) // skips spaces and punctuation.
			{
				if (islower(input[i][j])) // converts to caps as needed. 
				{
					input[i][j] = toupper(input[i][j]);
				}
				input[i][j] = MOD26char[((MOD26int[input[i][j]] + 26 - b) * a) % 26]; // performs affine decryption. 
																				// added 26 to account for negative values. 
			}
		}
	}
	return input;
}

void cipherShift(vector<vector<char> > text)
{
	cipher = text;
	choice = -1;
	while (choice != 0)
	{
		cout << "***Shift Cipher Menu***\n"
			<< "1.) Set shift value.\n"
			<< "2.) Encrypt string: shift = " << shift << "\n"
			<< "3.) Decrypt string: shift = " << shift << "\n"
			<< "4.) Decrypt string: shift unknown\n"
			<< "0.) Return to previous menu.\n\n"
			<< "Selection: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "\nEnter shift value (0 < n <= 25): ";
			cin >> shift;
			break;
		case 2:
			cout << "\nEncrypted string:\n";
			cipher = encryptAFFINE(text, 1, shift);
			displayToScreen(cipher);
			break;
		case 3:
			cout << "\nDecrypted string:\n";
			answer = decryptAFFINE(cipher, 1, shift);
			displayToScreen(answer);
			break;
		case 4:
			fout.open("output.txt");
			if (fout.is_open())
			{
				cout << "All possible shift values have been attempted and sent to \"output.txt\"\n";
				for (int i = 1; i < 26; i++)
				{
					answer = decryptAFFINE(cipher, 1, i);
					fout << "Shift = " << i << endl;
					displayToFile(answer, fout);
					fout << "\n\n";
				}
				fout.close();
			}
			else
			{
				cout << "Unable to open output file.\n";
			}
			break;
		case 0:
			cout << "Returning to previous menu...";
			break;
		default:
			cout << "Invalid input...\n";
			break;
		}
		puts("");
	}
}

void cipherMultiplicative(vector<vector<char> > text)
{
	cipher = text;
	choice = -1;
	while (choice != 0)
	{
		cout << "***Multiplicative Cipher Menu***\n"
			<< "1.) Set factor value.\n"
			<< "2.) Encrypt string: factor = " << factor << "\n"
			<< "3.) Decrypt string: factor = " << factor << "\n"
			<< "4.) Decrypt string: factor unknown\n"
			<< "0.) Return to previous menu.\n\n"
			<< "Selection: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			while (!done)
			{
				cout << "\nEnter factor value (must be invertible): ";
				cin >> factor;
				for (int i = 0; i < invertible.size(); i++)
				{
					if (invertible[i] == factor)
					{
						done = true;
					}
				}
				if (!done)
				{
					cout << factor << " is not invertible.\n";
				}
			}
			done = false;
			break;
		case 2:
			cout << "\nEncrypted string:\n";
			cipher = encryptAFFINE(text, factor, 0);
			break;
		case 3:
			cout << "\nDecrypted string:\n";
			answer = decryptAFFINE(cipher, MULinverse[factor], 0);
			displayToScreen(answer);
			break;
		case 4:
			fout.open("output.txt");
			if (fout.is_open())
			{
				cout << "All possible factor values have been attempted and sent to \"output.txt\"\n";
				for (int i = 1; i < 12; i++)
				{
					answer = decryptAFFINE(cipher, invertible[i], 0);
					fout << "Factor = " << invertible[i] << endl;
					displayToFile(answer, fout);
					fout << "\n\n";
				}
				fout.close();
			}
			else
			{
				cout << "Unable to open output file.\n";
			}
			break;
		case 0:
			cout << "Returning to previous menu...";
			break;
		default:
			cout << "Invalid input...\n";
			break;
		}
		puts("");
	}
}

void cipherAffine(vector<vector<char> > text)
{
	cipher = text;
	choice = -1;
	while (choice != 0)
	{
		cout << "***Affine Cipher Menu***\n"
			<< "1.) Set factor and shift values.\n"
			<< "2.) Encrypt string: factor = " << factor << " shift = " << shift << "\n"
			<< "3.) Decrypt string: factor = " << factor << " shift = " << shift << "\n"
			<< "4.) Decrypt string: factor and shift unknown\n"
			<< "0.) Return to previous menu.\n\n"
			<< "Selection: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			while (!done)
			{
				cout << "\nEnter factor value (must be invertible): ";
				cin >> factor;
				for (int i = 0; i < invertible.size(); i++)
				{
					if (invertible[i] == factor)
					{
						done = true;
					}
				}
				if (!done)
				{
					cout << factor << " is not invertible.\n";
				}
			}
			done = false;
			cout << "\nEnter shift value (0 < n <= 25): ";
			cin >> shift;
			break;
		case 2:
			cout << "\nEncrypted string:\n";
			cipher = encryptAFFINE(text, factor, shift);
			break;
		case 3:
			cout << "\nDecrypted string:\n";
			answer = decryptAFFINE(cipher, MULinverse[factor], shift);
			displayToScreen(answer);
			break;
		case 4:
			fout.open("output.txt");
			if (fout.is_open())
			{
				cout << "All possible factor and shift values have been attempted and sent to \"output.txt\"\n";
				for (int i = 0; i < 12; i++)
				{
					for (int j = 0; j < 26; j++)
					{
						answer = decryptAFFINE(cipher, invertible[i], j);
						fout << "Factor = " << invertible[i] << endl << "Shift = " << j << endl;
						displayToFile(answer, fout);
						fout << "\n\n";
					}
				}
				fout.close();
			}
			else
			{
				cout << "Unable to open output file.\n";
			}
			break;
		case 0:
			cout << "Returning to previous menu...";
			break;
		default:
			cout << "Invalid input...\n";
			break;
		}
		puts("");
	}
}