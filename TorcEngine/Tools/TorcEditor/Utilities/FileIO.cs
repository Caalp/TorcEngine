using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;
namespace TorcEditor
{
    public static class SerializeToXML<T>
    {
        public static void Write(T obj, string filepath)
        {
            System.Xml.Serialization.XmlSerializer writer = new System.Xml.Serialization.XmlSerializer(typeof(T));

            System.IO.FileStream file = null;
            if (!Directory.Exists(filepath))
            {
                file = System.IO.File.Create(filepath);
            }
            else
            {
                file = System.IO.File.Open(filepath, FileMode.Open);
            }

            try
            {
                writer.Serialize(file, obj);
                file.Close();
            }
            catch (Exception ex)
            {

                // this needs to be properly outputted 
                Debug.WriteLine(ex.Message);
            }


        }
    }

    public static class DeserializeXML<T>
    {
        public static T Read(string filepath)
        {

            System.Xml.Serialization.XmlSerializer serializer = new System.Xml.Serialization.XmlSerializer(typeof(T));

            // Declare an object variable of the type to be deserialized.
            T obj;

            using (Stream reader = new FileStream(filepath, FileMode.Open))
            {
                // Call the Deserialize method to restore the object's state.
                obj = (T)serializer.Deserialize(reader);
            }

            return obj;
        }
    }
}
