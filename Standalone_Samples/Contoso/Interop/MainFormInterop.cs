namespace Contoso.Interop
{
    public interface IMainFormInterop
    {
        void SwitchUI();
        ulong WindowHandle { get; } 
    }
}
