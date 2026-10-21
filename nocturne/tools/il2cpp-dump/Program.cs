// Use Il2CppDumper's parser on disk bytes with verified registration addresses.
// Avoid its Windows PE-loader fallback; no game code is loaded or executed here.
using System.Reflection;
using System.Security.Cryptography;
using Il2CppDumper;

if (args.Length != 5)
    throw new ArgumentException("Usage: StaticDump GameAssembly.dll global-metadata.dat output code-registration-hex metadata-registration-hex");
var metadataBytes = File.ReadAllBytes(args[1]);
var binaryBytes = File.ReadAllBytes(args[0]);
if (Convert.ToHexString(SHA256.HashData(binaryBytes)).ToLowerInvariant() != "59adbb5b18aaedc7df6c1672790ca48be99b5e8559c81db27132c436fb0a9fc4" ||
    Convert.ToHexString(SHA256.HashData(metadataBytes)).ToLowerInvariant() != "f911dd1f750c563313e061df5e7f2d8d2b6e6ab173a2b05f2f8ba398073753b3")
    throw new InvalidOperationException("Registration addresses are verified only for the inspected SMT3 HD build. Reinspect a changed build first.");
using var metadataStream = new MemoryStream(metadataBytes);
using var binaryStream = new MemoryStream(binaryBytes);
var metadata = new Metadata(metadataStream);
var binary = new PE(binaryStream);
binary.SetProperties(24.3, metadata.metadataUsagesCount);
binary.Init(Convert.ToUInt64(args[3], 16), Convert.ToUInt64(args[4], 16));
Console.WriteLine($"Metadata {metadata.Version}, native layout {binary.Version}, modules {binary.codeGenModules.Count}");
var program = typeof(Metadata).Assembly.GetType("Il2CppDumper.Program")!;
const BindingFlags flags = BindingFlags.NonPublic | BindingFlags.Static;
var config = new Config {
    DumpMethod = true, DumpField = true, DumpProperty = true,
    DumpAttribute = true, DumpFieldOffset = true, DumpMethodOffset = true,
    DumpTypeDefIndex = true, GenerateDummyDll = true, GenerateStruct = true,
    DummyDllAddToken = true, RequireAnyKey = false
};
program.GetField("config", flags)!.SetValue(null, config);
var output = Path.GetFullPath(args[2]) + Path.DirectorySeparatorChar;
Directory.CreateDirectory(output);
program.GetMethod("Dump", flags)!.Invoke(null, new object[] { metadata, binary, output });
if (!File.Exists(Path.Combine(output, "script.json")))
    throw new IOException("Il2CppDumper did not produce script.json");
