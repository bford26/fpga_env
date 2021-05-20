
#include "FPGAMiner.h"

bool Miner::init()
{

    cl_int err;
    std::vector<cl::Platform> platforms;

    cl::Platform::get(&platforms);

    if (platforms.empty())
    {
        printf("\nno platforms\n");
        return false;
    }

    // GET XILINX PLAT
    cl::Platform xilinx_platform;
    int pIdx;
    for(pIdx=0; pIdx<platforms.size(); pIdx++)
    {
        xilinx_platform = platforms[pIdx];

        std::string platformName = xilinx_platform.getInfo<CL_PLATFORM_NAME>(&err);
        if(platformName == "Xilinx")
        {
            break;
        }
    }


    // GET DEVICE
    std::vector<cl::Device> devices;
    devices.clear();
    xilinx_platform.getDevices(CL_DEVICE_TYPE_ACCELERATOR, &devices);
    if (devices.empty())
    {
        printf("\nno devices\n");
        return false;
    }

    for(int i=0; i<devices.size(); i++)
    {
        if(devices.size())
            m_device = devices[0];
    }    


    try
    {
        
        printf("INFO: loading xclbin kernel_func.xclbin\n");


        std::ifstream bin_file("kernel_func.xclbin", std::ifstream::binary);

        if( !bin_file.is_open())
        {
            printf("ERROR: failed to open xclbin file\n");
            return false;
        }

        bin_file.seekg (0, bin_file.end);
        unsigned nb = bin_file.tellg();
        bin_file.seekg (0, bin_file.beg);
        char *buf = new char [nb];
        bin_file.read(buf, nb);

        cl::Program::Binaries bins;
        bins.push_back({buf,nb});

        // create context
        m_context.clear();
        m_context.push_back(cl::Context(m_device, nullptr, nullptr, nullptr, &err));

        m_queue.clear();
        m_queue.push_back(cl::CommandQueue(m_context[0], m_device, CL_QUEUE_PROFILING_ENABLE/*CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE*/, &err));


        cl::Program program(m_context[0], {m_device}, bins, nullptr, &err);

        if (err != CL_SUCCESS)
        {
            std::cout << "Failed to program device[0] with xclbin file!\n";
        } 
        else
        {
            std::cout << "Device[0]: program successful!\n";
            // break; // we break because we found a valid device
        }

        m_make_dagItem_Kernel = cl::Kernel(program, "dagItem_krnl", &err);
        m_mixing_Kernel = cl::Kernel(program, "mixing_krnl", &err);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return true;
}

void Miner::workLoop()
{
    bool bResult = false;

    while(!bResult)
    {



    }


}

char Miner::nibbleToChar(unsigned nibble)
{
    return (char) ((nibble >= 10 ? 'a'-10 : '0') + nibble);
}
uint8_t Miner::charToNibble(char chr)
{
	if (chr >= '0' && chr <= '9')
	{
		return (uint8_t) (chr - '0');
	}
	if (chr >= 'a' && chr <= 'z')
	{
		return (uint8_t) (chr - 'a' + 10);
	}
	if (chr >= 'A' && chr <= 'Z')
	{
		return (uint8_t) (chr - 'A' + 10);
	}
	return 0;
}
std::vector<uint8_t> Miner::hexStringToBytes(char const* str)
{
	std::vector<uint8_t> bytes(strlen(str) >> 1);
	for (unsigned i = 0; i != bytes.size(); ++i)
	{
		bytes[i] = charToNibble(str[i*2 | 0]) << 4;
		bytes[i] |= charToNibble(str[i*2 | 1]);
	}
	return bytes;
}
std::string Miner::bytesToHexString(uint8_t const* bytes, unsigned size)
{
	std::string str;
	for (unsigned i = 0; i != size; ++i)
	{
		str += nibbleToChar(bytes[i] >> 4);
		str += nibbleToChar(bytes[i] & 0xf);
	}
	return str;
}


