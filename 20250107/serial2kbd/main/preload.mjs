import { ipcRenderer, contextBridge } from 'electron';

export default contextBridge.exposeInMainWorld('electron', {
  messaging: {
    send: (payload) => ipcRenderer.send('message', payload),
    on: (handler) => ipcRenderer.on('message', handler),
    off: (handler) => ipcRenderer.off('message', handler),
  },
});
