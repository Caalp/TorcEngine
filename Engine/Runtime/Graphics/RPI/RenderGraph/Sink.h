#pragma once

#include <memory>

class Source;

class Sink
{
public:
	Sink(const char* sinkName);
	void SetPassName(const char* passName);
	void SetTargetName(const char* targetName);
	const char* GetName() const;
	const char* GetPassName() const;
	const char* GetTargetName() const;
	virtual void Bind(Source& s) = 0;

private:
	const char* m_sinkName;
	const char* m_sinkTargetName;
	const char* m_sinkPassName;
};

template <class T>
class DirectBufferSink : public Sink
{
public:
	static std::unique_ptr<DirectBufferSink> Make(const char* name, std::shared_ptr<T>& target)
	{
		return std::make_unique<DirectBufferSink>(name, target);
	}

	DirectBufferSink(const char* name, std::shared_ptr<T>& target)
		: Sink(name)
		, m_directSink(target.get())
	{}

	void Bind(Source& source) override
	{
		auto p = reinterpret_cast<T*>(source.GetSource());
		m_isLinked = true;
		m_directSink = p;
	}

	bool IsLinked() const
	{
		return m_isLinked;
	}
	
protected:
	bool m_isLinked = false;
	T* m_directSink;
};

template <class T>
class BindableBufferSink : public Sink
{
public:
	static std::unique_ptr<BindableBufferSink> Make(const char* name, std::shared_ptr<T>& target)
	{
		return std::make_unique<BindableBufferSink>(name, target);
	}

	BindableBufferSink(const char* name, std::shared_ptr<T>& target)
		: Sink(name)
		, m_bindableSink(target.get())
	{}

	void Bind(Source& source) override
	{
		
	};
private:
	T* bindableSink;
};