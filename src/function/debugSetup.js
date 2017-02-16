import {TimeTickedFunction} from "./TimeTickedFunction";
import {ColorUtils} from "../utils/ColorUtils";

export class Func extends TimeTickedFunction{
  // Override base class
  drawFrame(draw, done){
    let colors = [... Array(this.config.numberOfLeds)]; // Array del tamaño de las luces

    draw(colors.map((v,i) => {
      return ColorUtils.HSVtoHex(Math.floor(i/50)/12, 1-(i%50)/50, this.config.brillo);
    }));
  }

  // Override and extend config Schema
  static configSchema(){
    let res = super.configSchema();
    res.brillo =  {type: Number, min: 0, max: 1, step: 0.01, default: 0.5}
    return res;
  }
}