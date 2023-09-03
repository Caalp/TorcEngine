#include "pch.h"
#include "FileStream.h"

InputStream::~InputStream()
{
	TE_DELETE_ALIGNED(m_buffer);
	m_inputStream.close();
}

void InputStream::Open(const char* file, std::fstream::openmode mode)
{
	m_inputStream.open(file, mode);
}

void InputStream::Read()
{
	if (m_inputStream.good())
	{
		uint32_t fileLength = GetFileLength();
		m_buffer = (uint8_t*)Memory::Alloc(fileLength, 1, MemoryTag::MEMORY_TAG_FILE_IO);

		m_inputStream.read((char*)m_buffer, fileLength);
	}
}

uint32_t InputStream::GetFileLength()
{
	m_inputStream.seekg(0, m_inputStream.end);
	uint32_t length = m_inputStream.tellg();
	m_inputStream.seekg(0, m_inputStream.beg);
	return length;
}

uint8_t* InputStream::Get()
{
	return m_buffer;
}

OutputStream::~OutputStream()
{
	m_ofs.close();
}

void OutputStream::Open(const char* file, std::fstream::openmode mode)
{
	m_ofs.open(file, mode);
}

void OutputStream::Write(uint8_t* buffer, size_t size)
{
	if (m_ofs.is_open())
	{
		m_ofs.write((char*)buffer, size);
	}
}
