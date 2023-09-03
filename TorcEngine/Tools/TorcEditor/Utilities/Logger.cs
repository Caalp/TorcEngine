using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;
using System.IO;
using System.Runtime.CompilerServices;
using System.Collections.ObjectModel;

namespace TorcEditor
{
    public static class Logger
    {
        private readonly static ObservableCollection<LogMessage> _logMessages = new ObservableCollection<LogMessage>();
        public static ObservableCollection<LogMessage> LogMessages { get; } = _logMessages;
        public static ObservableCollection<LogMessage> FilteredLogMessages { get; } = LogMessages;

        public static int LoggerFilter = (int)((LoggingLevel.Info) | LoggingLevel.Warning | LoggingLevel.Error | LoggingLevel.Fatal);

        public enum LoggingLevel : int
        {
            Info = 0x01,
            Warning = 0x02,
            Error = 0x04,
            Fatal = 0x08
        }

        public class LogMessage
        {
            public string logMsg { get; set; }
            public DateTime logTime { get; set; }
            public LoggingLevel logLevel { get; set; }
        }


        private static void Log(LoggingLevel loggingLvl, string msg, [CallerFilePath] string filePath = "", [CallerLineNumber] int lineNumber = 0)
        {
            LogMessage logMsg = new LogMessage();
            logMsg.logTime = DateTime.Now;
            logMsg.logMsg = msg;
            logMsg.logLevel = loggingLvl;
            _logMessages.Add(logMsg);
            FilterLogMessages();
        }

        public static void LogInfo(string msg, [CallerFilePath] string filePath = "", [CallerLineNumber] int lineNumber = 0)
        {
            Logger.Log(LoggingLevel.Info, msg, filePath, lineNumber);
        }
        public static void LogWarning(string msg, [CallerFilePath] string filePath = "", [CallerLineNumber] int lineNumber = 0)
        {
            Logger.Log(LoggingLevel.Warning, msg, filePath, lineNumber);
        }

        public static void LogError(string msg, [CallerFilePath] string filePath = "", [CallerLineNumber] int lineNumber = 0)
        {
            Logger.Log(LoggingLevel.Error, msg, filePath, lineNumber);
        }

        public static void FilterLogMessages()
        {
            FilteredLogMessages.Where(m => (((int)m.logLevel & (int)LoggerFilter)> 0) ? true : false);
        }
    }

}
