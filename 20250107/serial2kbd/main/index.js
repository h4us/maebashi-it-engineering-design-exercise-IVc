/**
 * --
 */

// Native
import * as path from 'node:path';

// Packages
import { BrowserWindow, app, screen } from 'electron';

import isDev from 'electron-is-dev';
import Store from 'electron-store';
import { SerialPort, ReadlineParser } from 'serialport';
import { mouse, Point, keyboard, Key } from '@nut-tree-fork/nut-js';
import { DateTime } from 'luxon';
import { Server as OSCServer } from 'node-osc';

// Project
import tables from './scancode-map.js';
console.info('Using tables:', tables);

const sleep = (ms) => new Promise(resolve => setTimeout(resolve, ms));

let mainWindow = false;

/*
 * Load application config, TODO: better defaults
 */
const settings = new Store({ name: 'settings' });
const _settings = {
  baudRate: (settings.baudRate ? parseInt(settings.baudRate) : 115200),
  delimiter: (settings.delimiter ? settings.delimiter : '\r\n')
};
console.info(`retrieve user settings from ${app.getPath('userData')}`, _settings);

const prepareMainWindow = async () => {
  /*
   * Application window, for debug only
   */
  mainWindow = new BrowserWindow({
    x: 0, y: 0,
    width: 800, height: 600,
    webPreferences: {
      // - Electron's bug?
      // - https://github.com/electron/forge/issues/2931
      nodeIntegrationInWorker: true,
      preload: path.join(import.meta.dirname, 'preload.mjs'),
    }
  });

  mainWindow.on('ready-to-show', async () => {
    if (isDev) mainWindow.webContents.openDevTools();

    mainWindow.webContents.send('message',
      `Versions: ${app.getVersion()} (Node.js ${process.version})`
    );

    await sleep(1000);

    mainWindow.webContents.send(
      'message', `Main window ready, @${DateTime.now().toString()}`
    );

    if (!isDev) mainWindow.minimize();
  });

  await mainWindow.loadFile('renderer/index.html');
};

const startupProcess = async () => {
  /*
   * Serialport devices
   */
  const ports = await SerialPort.list();
  console.info(ports);

  const serialportDevices = ports.filter(
    (el) => (
      /^Microsoft.*/.test(el.manufacturer) || /^Arduino.*/.test(el.manufacturer) || /^COM[0-9]+$/.test(el.path)
    )
  );

  for (let device of serialportDevices) {
    const { path, serialNumber, vendorId } = device;
    const baudRate = _settings.baudRate;
    const deviceType = 'serial';
    const sp = new SerialPort({ path, baudRate });
    const sp_parser = sp.pipe(new ReadlineParser({ delimiter: _settings.delimiter }));

    console.info('using serialport:', path, baudRate, deviceType);
    if (mainWindow) {
      mainWindow.webContents.send(
        'message', `use serialport: ${path}, ${baudRate}, ${deviceType}`
      );
    }

    sp_parser.on('data', async (data) => {
      const [addr, ...rest] = data.split(' ');

      if (addr && addr == '/type') {
        console.info(addr, rest);
        await keyboard.type(rest.join());
      } else if (addr && addr == '/type_raw') {
        console.info(addr, rest);
        const enumKeySeq = rest.map((el) => Key[el]);
        await keyboard.type(...enumKeySeq);
      } else if (addr && addr == '/press') {
        console.info(addr, rest);
        const enumKeySeq = rest.map((el) => Key[el]);
        await keyboard.pressKey(...enumKeySeq);
      } else if (addr && addr == '/release') {
        console.info(addr, rest);
        const enumKeySeq = rest.map((el) => Key[el]);
        await keyboard.releaseKey(...enumKeySeq);
      } else {
        console.error('invalid data format ', data);
      }
    });
  }

  /*
   * OSC devices, for debug, TODO:
   */
  const oscDevice = new OSCServer(9999, '0.0.0.0');

  oscDevice.on('message', async (e) => {
    const [addr, ...data] = e;

    console.log(addr, data);

    if (addr == '/type') {
      await keyboard.type(data.join());
    } else if (addr == '/type_raw') {
      const enumKeySeq = data.map((el) => Key[el]);
      await keyboard.type(...enumKeySeq);
    } else if (addr == '/press') {
      const enumKeySeq = data.map((el) => Key[el]);
      await keyboard.pressKey(...enumKeySeq);
    } else if (addr == '/release') {
      const enumKeySeq = data.map((el) => Key[el]);
      await keyboard.releaseKey(...enumKeySeq);
    } else {
      console.error('invalid data format ', data);
    }
  });

  console.info(`--startupProcess done @${DateTime.now().toString()})`);
  if (mainWindow) {
    mainWindow.webContents.send(
      'message', `--startupProcess done @${DateTime.now().toString()})`
    );
  }
};

app.on('ready', async () => {
  await prepareMainWindow();
  await startupProcess();
});

// Quit the app once all windows are closed
app.on('window-all-closed', async () => {
  app.quit();
});
