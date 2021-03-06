import {ColorUtils} from "../utils/ColorUtils";
import {SoundBasedFunction} from "./SoundBasedFunction";

export class Func extends SoundBasedFunction{
  constructor(config, leds) {
    super(config, leds);
  }

  start(config, draw, done){
    this.lastVolume = new Array(this.numberOfLeds+1).join('0').split('').map(() => "#000000");
    this.time = 0;
    this.maxVolume = 0;

    super.start(config, draw, done)
  }

  // Override parent method
  drawFrame(draw, done){
    this.time += this.config.speed;

    let vol = this.averageVolume*this.config.multiplier;

    // Como las luces tenues son MUY fuertes igual, a partir de cierto valor "las bajamos"
    if(vol < this.config.cutThreshold){
      vol = vol/3*0;
    }

    let newVal = ColorUtils.HSVtoHex((vol*4+this.time/2000)%1, 1, Math.min(vol*vol*10, 1));

    for(let i=0;i<this.config.speed;i++) {
      if(this.config.doble){
        if(this.config.haciaAfuera) {
          this.lastVolume.splice(this.numberOfLeds-1, 1);
          this.lastVolume.splice(0, 1);
          this.lastVolume.splice(this.lastVolume.length/2, 0, newVal);
          this.lastVolume.splice(this.lastVolume.length/2, 0, newVal);
        } else {
          this.lastVolume.splice(Math.floor(this.numberOfLeds / 2 - 1), 2);
          this.lastVolume.unshift(newVal);
          this.lastVolume.push(newVal);
        }
      } else {
        this.lastVolume.splice(this.numberOfLeds-1, 1);
        this.lastVolume.unshift(newVal);
      }
    }

    draw(this.lastVolume);
    done();
  }

  static presets(){
    return {
      slowDoble: {speed: 1, doble: true},
      fastSimple: {speed: 5, doble: false},
      fastDobleDesdePuntas: {speed: 5, doble: true, haciaAfuera: false},
      fastDobleDesdeCentro: {speed: 5, doble: true, haciaAfuera: true},
    }
  }

  // Override and extend config Schema
  static configSchema(){
    let res = super.configSchema();
    res.multiplier = {type: Number, min: 0, max: 2, step: 0.01, default: 3};
    res.speed = {type: Number, min: 1, max: 30, step: 1, default: 1};
    res.cutThreshold = {type: Number, min: 0, max: 1, step: 0.01, default: 0.1};
    res.doble = {type: Boolean, default: false};
    res.haciaAfuera = {type: Boolean, default: true};
    return res;
  }
}