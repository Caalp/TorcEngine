#pragma once
#include <memory>
#include <string>

class IGPUResource;

class Source
{
public:
	const char* GetName() const;
	virtual IGPUResource* GetSource() { return 0; }
	virtual ~Source() = default;
	//std::string& GetSinkName() const;
protected:
	Source(const char* sourceName);
private:
	const char* m_name;
};

template <class T>
class DirectBufferSource : public Source
{

public:
	static std::unique_ptr<DirectBufferSource> Make(const char* name, std::shared_ptr<T>& target)
	{
		return std::make_unique<DirectBufferSource>(name, target);
	}

	DirectBufferSource(const char* name, std::shared_ptr<T>& target)
		: Source(name)
		, m_directSource(target.get())
	{}

	virtual IGPUResource* GetSource()
	{
		m_isLinked = true;
		return (IGPUResource*)m_directSource;
	}
private:
	bool m_isLinked = false;
	T* m_directSource;

};

template <class T>
class BindableBufferSource : public Source
{
public:
	static std::unique_ptr<BindableBufferSource> Make(const char* name, std::shared_ptr<T>& source)
	{
		return std::make_unique<BindableBufferSource>(name, source);
	}
	BindableBufferSource(std::string name, std::shared_ptr<T>& source) 
		: Source(name)
		, bindableSource(source.get())
	{}
	virtual IGPUResource* GetSource() override
	{
		isLinked = true;
		return (IGPUResource*)bindableSource;
	}
private:
	bool m_isLinked = false;
	T* m_bindableSource;
};