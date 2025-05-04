#pragma once
#include "Core/IO/Path/Path.h"
#include <variant>
#include <vector>

namespace Torc
{
	namespace IO
	{
		class FileStream;
	}

	namespace Json
	{
		enum class EResult
		{
			Success,
			NoOpenFileStream,
			FailedToOpenFileStream,
			InvaliedJsonString,
			FailedToParse,
			Failure
		};

		enum class ValueTypes
		{
			Int64,
			UInt64,
			Float,
			Double,
			Bool,
			String,
			Array,
			Numeric,
			Object,
			Invalid
		};

		struct ValueBase
		{
			ValueBase(ValueTypes valueType) 
				: type(valueType)
			{}
			const ValueTypes type;
		};

		struct ValueInvalid : ValueBase
		{
			ValueInvalid()
				: ValueBase(ValueTypes::Invalid)
			{}
			//static const ValueTypes type = ValueTypes::Invalid;
		};

		struct JsonObject : ValueBase
		{
			JsonObject()
				: ValueBase(ValueTypes::Object)
			{}
			std::vector<ValueBase*> values;
			//static const ValueTypes type = ValueTypes::Object;
		};

		struct JsonArray : ValueBase
		{
			JsonArray()
				: ValueBase(ValueTypes::Array)
			{}

			struct ArrayData
			{
				uint32 size;
				ValueBase* values;
			};
			
			ArrayData data;
			//static const ValueTypes type = ValueTypes::Array;
		};

		struct ValueNumeric : ValueBase
		{
			ValueNumeric()
				: ValueBase(ValueTypes::Numeric)
			{}
			double value;
			//static const ValueTypes type = ValueTypes::Numeric;
		};

		template<typename T, ValueTypes typeValue>
		struct ValueGeneric : ValueBase
		{
			ValueGeneric()
				: ValueBase(typeValue)
			{}
			ValueGeneric(const T& v)
				: value(v)
				, ValueBase(typeValue)
			{
				//this->type = typeValue;
			}

			T value;
			//static const ValueTypes type = typeValue;
		};

		typedef ValueGeneric<Std::string, ValueTypes::String> JsonString;
		typedef ValueGeneric<uint64, ValueTypes::UInt64> JsonUInt64;
		typedef ValueGeneric<int64, ValueTypes::Int64> JsonInt64;
		typedef ValueGeneric<bool, ValueTypes::Bool> JsonBool;
		typedef ValueGeneric<float, ValueTypes::Float> JsonFloat;
		typedef ValueGeneric<double, ValueTypes::Double> JsonDouble;
		typedef ValueGeneric<ValueInvalid, ValueTypes::Invalid> JsonInvalid;

		class JsonValue final
		{
		public:

			template<typename T, ValueTypes valueType>
			JsonValue(ValueGeneric<T, valueType>& val);

			~JsonValue();

			Std::string String();
			uint64 Uint64();
			int64 Int64();
			float Float();
			bool Bool();
			double Double();
		
			ValueBase* m_value;
		};

		class JsonDocument
		{
		public:
			JsonDocument();
			~JsonDocument();
			uint8* GetBuffer();
			void AllocateBuffer(uint64 bufferSize);
			void Parse();

			JsonValue GetValue(const char* str);
		private:
			void* m_nativeDoc;
			uint8* m_buffer;
		};

		class JsonReader
		{
		public:
			JsonReader();
			~JsonReader();

			//! Open a FileStream from a given path
			EResult OpenStream(const Path& jsonPath);

			//! Close file stream if already opened
			EResult CloseStream();
			JsonDocument& ReadAndParseStream();
			JsonDocument& ParseFromString(const Std::string& jsonString);

		private:
			IO::FileStream* m_stream;
			JsonDocument m_document;
		};
	}
}
