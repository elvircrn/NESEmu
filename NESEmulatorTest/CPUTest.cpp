#include "CppUnitTest.h"
#include "../NES Emulator/CPU.h"
#include "../NES Emulator/FileHandler.h"
#include <experimental\filesystem>
#include "../NES Emulator/Debugger.h"

#include <iomanip>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NESEmulatorTest
{		
#define ASRT(X, Y) Assert::AreEqual((X), (Y), L"V test failed", LINE_INFO());

	void LoggerDump(const Debugger &debugger)
	{
		Logger::WriteMessage(debugger.GetOpHistForLogging().c_str());
		//Logger::WriteMessage(debugger.GetPCHistForLogging().c_str());
	}

	TEST_CLASS(CPUFlagTest)
	{
	public:
		
		TEST_METHOD(FlagSet)
		{
			CPU cpu;
			cpu.SetFlag(Flags::V, 1);
			Assert::AreEqual(cpu.GetFlag(Flags::V), true, L"V test failed", LINE_INFO());
		}
		
		TEST_METHOD(UpdateV)
		{
			CPU cpu;

			cpu.UpdV(0x80, 0x80, 0);
			Assert::AreEqual(cpu.GetFlag(Flags::V), true, L"Test failed", LINE_INFO());

			cpu.UpdV(0x9, 0x5, 0xE);
			Assert::AreEqual(cpu.GetFlag(Flags::V), false, L"Test failed", LINE_INFO());

			cpu.UpdV(0x40, 0x40, 0x80);
			Assert::AreEqual(cpu.GetFlag(Flags::V), true, L"Test failed", LINE_INFO());
		}

		TEST_METHOD(UpdateC)
		{
			CPU cpu;

			cpu.UpdC(0xff, 0xff, 0xff + 0xff);
			Assert::AreEqual(cpu.GetFlag(Flags::C), true, L"Test failed", LINE_INFO());

			cpu.UpdC(0, 1, 1);
			Assert::AreEqual(cpu.GetFlag(Flags::C), false, L"Test failed", LINE_INFO());
		}

		TEST_METHOD(UpdateNZ)
		{
			CPU cpu;

			cpu.UpdN(0);
			ASRT(cpu.GetFlag(Flags::N), false);

			cpu.UpdN(0x80);
			ASRT(cpu.GetFlag(Flags::N), true);

			cpu.UpdZ(0);
			ASRT(cpu.GetFlag(Flags::Z), true);

			cpu.UpdZ(1);
			ASRT(cpu.GetFlag(Flags::Z), false);
		}

		TEST_METHOD(NESTest)
		{
			auto filepath = std::experimental::filesystem::path(__FILE__)
				.parent_path()
				.append("nestest.nes")
				.string();

			ROM rom = (FileHandler())
				.LoadCartridge(filepath);

			CPU cpu;
			Debugger debugger(&cpu);
			cpu.PowerUp();
			cpu.LoadCartridge(rom);
			cpu.SetP(0x24);

			auto res = std::experimental::filesystem::path(__FILE__)
				.parent_path()
				.append("res.txt")
				.string();

			std::ifstream myfile(res);
			std::string line;
			std::vector<std::string> lines;
			while (std::getline(myfile, line))
				lines.push_back(line);

			for (int i = 0; i < 8000; i++)
			{
				std::string line = debugger.GetNESTestLine();
				std::string correctLine = lines[i];

				debugger.AppendStatHist(line);
				
				//Assert::AreEqual(lines[i], line, std::to_wstring(cpu.GetPC()).c_str(), LINE_INFO());
				if (correctLine != line)
				{
					LoggerDump(debugger);
					Logger::WriteMessage(("Exp: " + correctLine + "\nFnd: " + line).c_str());
					Logger::WriteMessage(("Failed at: " + std::to_string(i)).c_str());
					std::stringstream ss;
					ss << std::hex << std::setfill('0') << std::setw(2) << (int)cpu.GetPC();
					Logger::WriteMessage(("PC: " + ss.str()).c_str());
					Assert::Fail();
				}
				try
				{
					cpu.Execute();
				}
				catch (std::string e)
				{
					Assert::Fail();
				}
			}
		}
	};
}