#include "Json/JsonReader.h"
#include "IO/FileStream.h"
#include "Logging/Logger.h"
#include <RapidJSON/document.h>

namespace Torc
{
	namespace Json
	{
		template<ValueTypes a, std::enable_if_t<a == ValueTypes::String, bool> = true>
		struct CreateJsonType
		{
			void* operator new(size_t size)
			{
				return new JsonString;
			}
		};

		JsonReader::JsonReader()
			: m_stream(nullptr)
		{
		}

		JsonReader::~JsonReader()
		{
			if (m_stream)
			{
				if (m_stream->GetStatus() == IO::EStatus::Open)
				{
					m_stream->Close();
				}
				delete m_stream;
			}
		}

		EResult JsonReader::OpenStream(const Path& jsonPath)
		{
			IO::FileStream* stream = new IO::FileStream;
			IO::Result res = stream->Open(jsonPath, IO::OpenMode::Read);
			if (res.m_resultCode != IO::Result::Success)
			{
				TE_Error(LogChannel::LC_Core, "Failed to open file stream for path %s", jsonPath.GetView().c_str());
				return EResult::FailedToOpenFileStream;
			}
			m_stream = stream;
			return EResult::Success;
		}

		EResult JsonReader::CloseStream()
		{
			if (m_stream->GetStatus() == IO::EStatus::Open)
			{
				m_stream->Close();
			}
			return EResult::Success;
		}

		JsonDocument& Torc::Json::JsonReader::ReadAndParseStream()
		{
			if (!m_stream)
			{
				return m_document;
			}

			const IO::SizeType fileLength = m_stream->GetLength();
			m_document.AllocateBuffer(fileLength);
			uint8* buffer = m_document.GetBuffer();
			m_stream->Read(buffer, fileLength);
			m_document.Parse();
			return m_document;
		}

		JsonDocument& Torc::Json::JsonReader::ParseFromString(const Std::string& jsonString)
		{
			m_document.AllocateBuffer(jsonString.length());
			uint8* buffer = m_document.GetBuffer();
			m_document.Parse();
			return m_document;
		}

		JsonDocument::JsonDocument()
			: m_buffer (nullptr)
			, m_nativeDoc(new rapidjson::Document)
		{
		}

		JsonDocument::~JsonDocument()
		{
			if (m_nativeDoc)
			{
				delete static_cast<rapidjson::Document*>(m_nativeDoc);
			}

			if (m_buffer)
			{
				delete m_buffer;
			}
		}

		uint8* JsonDocument::GetBuffer()
		{
			return m_buffer;
		}

		void JsonDocument::AllocateBuffer(uint64 bufferSize)
		{
			if (!m_buffer)
			{
				m_buffer = new uint8[bufferSize + 1];
				Platform::MemZero(m_buffer, bufferSize + 1);
			}
		}

		void JsonDocument::Parse()
		{
			rapidjson::Document* doc = (rapidjson::Document*)m_nativeDoc;
			doc->Parse((const char*)m_buffer);
		}

		JsonValue JsonDocument::GetValue(const char* str)
		{
			rapidjson::Document& doc = *(rapidjson::Document*)m_nativeDoc;

			auto ss = sizeof(ValueBase);
			auto ss2 = sizeof(ValueGeneric<int, ValueTypes::Array>);
			auto ss3 = sizeof(ValueNumeric);
			auto ss4 = sizeof(std::variant< JsonString>);
			auto ss5 = sizeof(JsonString);
			auto ss6 = sizeof(JsonDouble);

			bool hasMember = doc.HasMember(str);
			if (!hasMember)
			{
				//return *{ new { JsonInvalid{} } };
			}
						
			auto& value = doc.operator[](str);
			if (value.IsObject())
			{

			}

			if (value.IsArray())
			{
				auto& arr = value.GetArray();
				JsonArray* arr2 = new JsonArray();
				for (auto& e : arr)
				{
					rapidjson::Type type = e.GetType();
					ValueTypes jType;

					switch (type)
					{
					case rapidjson::kNullType:
					jType = ValueTypes::Invalid;
					break;
					case rapidjson::kFalseType:
					case rapidjson::kTrueType:
					jType = ValueTypes::Bool;
					break;
					case rapidjson::kObjectType:
					jType = ValueTypes::Object;
					break;
					case rapidjson::kArrayType:
					jType = ValueTypes::Array;
					break;
					case rapidjson::kStringType:
					jType = ValueTypes::String;
					break;
					case rapidjson::kNumberType:
					jType = ValueTypes::Numeric;
					break;
					default:
					jType = ValueTypes::Invalid;
					break;
					}
					


					bool t = e.Is<int>();
					if (t)
					{
						ValueGeneric<std::vector<int>, ValueTypes::Array> newArray2;
						newArray2.value.push_back(e.GetInt());
					}
					t = e.IsString();
					if (t)
					{
						ValueGeneric<std::vector<Std::string>, ValueTypes::Array> newArray2;
						newArray2.value.push_back(e.GetString());
					}
					
					
					//newArray.value.push_back(0);
				}

			}
			else if (value.IsObject())
			{
				/*auto& arr = value.GetObject();
				ValueGeneric<std::vector<std::decay_t<decltype(arr)>>, ValueTypes::Array> newArray;
				for (const auto& e : arr)
				{
					const auto& n = e.name;
					Std::string v = e.value.GetString();
				}*/
			}
			else if (value.IsString())
			{
				ValueTypes vv = ValueTypes::String;
				//auto s = new CreateJsonType<decltype(vv)>();
				JsonString* jVal = new JsonString { value.GetString() };
				return { *jVal };
			}
			else if (value.IsUint64())
			{
				JsonUInt64* jVal = new JsonUInt64{ value.GetUint64() };
				return JsonValue{ *jVal };
			}
			else if (value.IsInt64())
			{
				JsonInt64 jVal{ value.GetInt64()};
				return JsonValue{ jVal };
			}
			// Note: reading double as float as well
			else if (value.IsFloat())
			{
				JsonFloat* jVal = new JsonFloat{ value.GetFloat() };
				return JsonValue{ *jVal };
			}
			else if (value.IsDouble())
			{
				JsonDouble* jVal = new JsonDouble{ value.GetDouble() };
				return JsonValue{ *jVal };
			}
			else if (value.IsBool())
			{
				JsonBool* jVal = new JsonBool{ value.GetBool() };
				return JsonValue{ *jVal };
			}

			JsonInvalid* v = new JsonInvalid{ };
			JsonValue newVal = JsonValue{ *v };
			
			return newVal;
		}

		template<typename T, ValueTypes valueType>
		JsonValue::JsonValue(ValueGeneric<T, valueType>& val)
			: m_value(&val)
		{
		}

		JsonValue::~JsonValue()
		{
			if (m_value)
			{
				delete m_value;
			}
		}

		Std::string JsonValue::String()
		{
			return static_cast<JsonString*>(m_value)->value;
		}
		uint64 JsonValue::Uint64()
		{
			return static_cast<JsonUInt64*>(m_value)->value;
		}
		int64 JsonValue::Int64()
		{
			return static_cast<JsonInt64*>(m_value)->value;
		}
		float JsonValue::Float()
		{
			return static_cast<JsonFloat*>(m_value)->value;
		}
		bool JsonValue::Bool()
		{
			return static_cast<JsonBool*>(m_value)->value;
		}
		double JsonValue::Double()
		{
			return static_cast<JsonDouble*>(m_value)->value;
		}
}
}
