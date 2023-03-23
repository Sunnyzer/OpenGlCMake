using System;
using System.IO;
using System.Text.RegularExpressions;

namespace PostBuildExe
{
    static class Program
    {
        static void Main(string[] _args)
        {
            string _directory = _args[0] + "\\MonoBehaviour";
            string[] _files = Directory.GetFiles(_directory);
            for (int i = 0; i < _files.Length; ++i)
            {
                string _filePath = _files[i];
                if (_filePath.Contains(".cpp")) continue;

                string _fileText = File.ReadAllText(_filePath);
                Match _match;
                _match = Regex.Match(_fileText, @"(class([ ]{0,})(\w+)([ ]{0,}):)");
                if (!_match.Success) continue;
                string className = _match.Value.Replace("class", "").Replace(":", "").Trim();
                _match = Regex.Match(_fileText, @"(:([ ]{0,})(public([ ]{0,})\w+))");
                string parentClassName = _match.Value;

                if (!string.IsNullOrEmpty(parentClassName))
                {
                    parentClassName = parentClassName.TrimEnd();
                    parentClassName = parentClassName.Substring(parentClassName.LastIndexOf(' ') + 1);
                }
                string _cloneText = "CLONE(" + className + ");";
                if (!_fileText.Contains(_cloneText))
                {
                    string _tempFileText = _fileText;
                    _fileText = Regex.Replace(_fileText, @"(([ ]{0,})(CLONE([ ]{0,})\((\w+)([ ]{0,})\)([ ]{0,});))", "");
                    _match = Regex.Match(_fileText, @"(:([ ]{0,})(public([ ]{0,})(\w+)([ ]{0,})))");
                    if (_match.Success)
                    {
                        _fileText = _fileText.Insert(_match.Index + _match.Value.Length + 3, "\n    " + _cloneText);
                    }
                }
                else
                {
                    _fileText = Regex.Replace(_fileText, @"(([ ]{0,})(CLONE ([ ]{0,})\((\w+)([ ]{0,})\)([ ]{0,});))", "");
                }

                if (_fileText.Contains("REGISTERFACTORY(" + parentClassName + "," + className + ")"))
                {
                    File.WriteAllText(_filePath, _fileText);
                    continue;
                }
                _match = Regex.Match(_fileText, @"(REGISTERFACTORY([ ]{0,})\(([ ]{0,})(\w+)([ ]{0,}),([ ]{0,})(\w+)([ ]{0,})\)([ ]{0,}))");
                if (_match.Success)
                {
                    _fileText = _fileText.Replace(_match.Value, "");
                }
                else
                    _fileText += "\n";

                File.WriteAllText(_filePath, _fileText + "REGISTERFACTORY(" + parentClassName + "," + className + ")");
            }
        }
    }
}
