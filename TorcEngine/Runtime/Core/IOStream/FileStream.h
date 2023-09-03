#pragma once

class InputStream
{
public:
	InputStream() = default;
	~InputStream();

	/**
	 * 
	 */
	void Open(const char* file, std::fstream::openmode mode = std::fstream::in);

	/**
	 * Reads opened file into a buffer
	 * 
	 * @return pointer to the beginning of the buffer
	 */
	void Read();

	/**
	 * Retrieves and returns the file length in bytes.
	 * 
	 * @return file length in bytes
	 */
	uint32_t GetFileLength();
	
	uint8_t* Get();

protected:
	std::ifstream m_inputStream;
	uint8_t* m_buffer;
};

class OutputStream
{
public:
	~OutputStream();

	void Open(const char* file, std::fstream::openmode mode = std::fstream::out);

	void Write(uint8_t* buffer, size_t size);

private:
	std::ofstream m_ofs;
};

class ByteInputStream : public InputStream
{
public:
	
	template<typename T>
	void Open(const char* file);

	template<typename T>
	T* Read();


};

class ByteOutputStream : public OutputStream
{
public:
	template<typename T>
	void Open(const char* file);

	template<typename T>
	void Write(T* buffer, size_t size);

};

template<typename T>
inline void ByteInputStream::Open(const char* file)
{
	InputStream::Open(file, std::fstream::binary);
}

template<typename T>
inline T* ByteInputStream::Read()
{
	InputStream::Read();
	return (T*)m_buffer;
}

template<typename T>
inline void ByteOutputStream::Open(const char* file)
{
	OutputStream::Open(file, std::fstream::binary);
}

template<typename T>
inline void ByteOutputStream::Write(T* buffer, size_t size)
{	
	OutputStream::Write((uint8_t*)buffer, size);
}
