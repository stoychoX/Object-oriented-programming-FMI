#include <iostream>
#include <fstream>

struct JobInvitation {
	char FirmName[25];
	int NumberOfMembers = 0;
	int PaidVacationDays = 0;
	int PriceAfterFinishedProject = 0;
};

void writeInfoIntoStructArr(JobInvitation* myInvitArr, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		std::cin >> myInvitArr[i].FirmName;
		std::cin >> myInvitArr[i].NumberOfMembers;
		std::cin >> myInvitArr[i].PaidVacationDays;
		std::cin >> myInvitArr[i].PriceAfterFinishedProject;
	}
}

bool saveInvitationsToFile(const char* filePath, const size_t n, const JobInvitation* myInvitArr)
{
	std::ofstream myFile(filePath, std::ios::binary | std::ios::app);
	if (!myFile.is_open())
	{
		return false;
	}
	myFile.write((const char*)myInvitArr, sizeof(JobInvitation) * n);
	myFile.close();
}

int getFileSize(std::ifstream& myFile)
{
	int currPos = myFile.tellg();
	myFile.seekg(0, std::ios::end);
	int fileSize = myFile.tellg();
	myFile.seekg(currPos);
	return fileSize;
}

bool saveFileToInvitArr(const char* filePath, JobInvitation* myInvitArr)
{
	std::ifstream myFile(filePath);
	if (!myFile.is_open())
	{
		return false;
	}
	int structsInFile = getFileSize(myFile) / sizeof(JobInvitation);
	myFile.read((char*)myInvitArr, sizeof(JobInvitation) * structsInFile);
	myFile.close();
}

bool filterOffer(const char* filePath, size_t minSalary)
{
	std::ifstream myFile(filePath);
	if (!myFile.is_open())
	{
		return false;
	}
	int numberStructsInFile = getFileSize(myFile) / sizeof(JobInvitation);
	JobInvitation* myInvitArr = new JobInvitation[numberStructsInFile];
	saveFileToInvitArr(filePath, myInvitArr);
	for (int i = 0; i < numberStructsInFile; i++)
	{
		if (myInvitArr[i].PriceAfterFinishedProject > minSalary)
		{
			std::cout << myInvitArr[i].FirmName << " "
				<< myInvitArr[i].NumberOfMembers << " "
				<< myInvitArr[i].PaidVacationDays << " "
				<< myInvitArr[i].PriceAfterFinishedProject << std::endl;
		}
	}
	myFile.close();
	delete[] myInvitArr;
	return true;
}

bool findOffer(const char* filePath, const char* name)
{
	std::ifstream myFile("test.txt");
	if (!myFile.is_open())
	{
		return false;
	}
	int numberOfStructs = getFileSize(myFile) / sizeof(JobInvitation);
	JobInvitation* invitArray = new JobInvitation[numberOfStructs];
	saveFileToInvitArr(filePath, invitArray);
	for (int i = 0; i < numberOfStructs; i++)
	{
		if (strcmp(invitArray[i].FirmName, name) == 0)
		{
			std::cout << "Offer like this exists!" << std::endl;
			std::cout << invitArray[i].FirmName << " "
				<< invitArray[i].NumberOfMembers << " "
				<< invitArray[i].PaidVacationDays << " "
				<< invitArray[i].PriceAfterFinishedProject << std::endl;
		}
		else
		{
			std::cout << "Offer like this DOES NOT exist!" << std::endl;
		}
	}
	myFile.close();
	delete[] invitArray;
}

int main()
{
	int n = 0;
	std::cin >> n;
	JobInvitation* InvitationsArr = new JobInvitation[n];
	std::ifstream myFile("test.txt", std::ios::binary | std::ios::app);
	writeInfoIntoStructArr(InvitationsArr, n);
	saveInvitationsToFile("test.txt", n, InvitationsArr);
	filterOffer("test.txt", 500);
	findOffer("test.txt", "matherHOOD1");
}