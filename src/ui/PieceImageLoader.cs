using System;
using System.Collections.Generic;
using System.Text;
using shoryu.interop;

namespace UI
{
    internal class PieceImageLoader
    {
        static private readonly Image ImgSenteFu = Image.FromFile("Images/Fu.png");
        static private readonly Image ImgSenteKyo = Image.FromFile("Images/Kyosya.png");
        static private readonly Image ImgSenteKei = Image.FromFile("Images/Keima.png");
        static private readonly Image ImgSenteGin = Image.FromFile("Images/Gin.png");
        static private readonly Image ImgSenteKin = Image.FromFile("Images/Kin.png");
        static private readonly Image ImgSenteKaku = Image.FromFile("Images/Kaku.png");
        static private readonly Image ImgSenteHisha = Image.FromFile("Images/Hisya.png");
        static private readonly Image ImgOu = Image.FromFile("Images/Osyo.png");
        static private readonly Image ImgSenteTokin = Image.FromFile("Images/Tokin.png");
        static private readonly Image ImgSenteNariKyo = Image.FromFile("Images/Nari_Kyo.png");
        static private readonly Image ImgSenteNariKei = Image.FromFile("Images/Nari_Kei.png");
        static private readonly Image ImgSenteNariGin = Image.FromFile("Images/Nari_Gin.png");
        static private readonly Image ImgSenteUma = Image.FromFile("Images/Uma.png");
        static private readonly Image ImgSenteRyu = Image.FromFile("Images/Ryu.png");

        static private readonly Image ImgGoteFu = RotateImage(ImgSenteFu);
        static private readonly Image ImgGoteKyo = RotateImage(ImgSenteKyo);
        static private readonly Image ImgGoteKei = RotateImage(ImgSenteKei);
        static private readonly Image ImgGoteGin = RotateImage(ImgSenteGin);
        static private readonly Image ImgGoteKin = RotateImage(ImgSenteKin);
        static private readonly Image ImgGoteKaku = RotateImage(ImgSenteKaku);
        static private readonly Image ImgGoteHisha = RotateImage(ImgSenteHisha);
        static private readonly Image ImgGyoku = RotateImage(Image.FromFile("Images/Gyoku.png"));
        static private readonly Image ImgGoteTokin = RotateImage(ImgSenteTokin);
        static private readonly Image ImgGoteNariKyo = RotateImage(ImgSenteNariKyo);
        static private readonly Image ImgGoteNariKei = RotateImage(ImgSenteNariKei);
        static private readonly Image ImgGoteNariGin = RotateImage(ImgSenteNariGin);
        static private readonly Image ImgGoteUma = RotateImage(ImgSenteUma);
        static private readonly Image ImgGoteRyu = RotateImage(ImgSenteRyu);

        static private Image RotateImage(Image source)
        {
            var rotated = (Image)source.Clone();
            rotated.RotateFlip(RotateFlipType.Rotate180FlipNone);
            return rotated;
        }

        static private readonly Dictionary<ManagedPieceCode, Image> PieceImageMap = new()
        {
            { ManagedPieceCode.SenteFu, ImgSenteFu },
            { ManagedPieceCode.SenteKyo, ImgSenteKyo },
            { ManagedPieceCode.SenteKei, ImgSenteKei },
            { ManagedPieceCode.SenteGin, ImgSenteGin },
            { ManagedPieceCode.SenteKin, ImgSenteKin },
            { ManagedPieceCode.SenteKaku, ImgSenteKaku },
            { ManagedPieceCode.SenteHisya, ImgSenteHisha },
            { ManagedPieceCode.Ou, ImgOu },
            { ManagedPieceCode.SenteTokin, ImgSenteTokin },
            { ManagedPieceCode.SenteNariKyo, ImgSenteNariKyo },
            { ManagedPieceCode.SenteNariKei, ImgSenteNariKei },
            { ManagedPieceCode.SenteNariGin, ImgSenteNariGin },
            { ManagedPieceCode.SenteUma, ImgSenteUma },
            { ManagedPieceCode.SenteRyu, ImgSenteRyu },
            { ManagedPieceCode.Gyoku, ImgGyoku },
            { ManagedPieceCode.GoteFu, ImgGoteFu },
            { ManagedPieceCode.GoteKyo, ImgGoteKyo },
            { ManagedPieceCode.GoteKei, ImgGoteKei },
            { ManagedPieceCode.GoteGin, ImgGoteGin },
            { ManagedPieceCode.GoteKin, ImgGoteKin },
            { ManagedPieceCode.GoteKaku, ImgGoteKaku },
            { ManagedPieceCode.GoteHisya, ImgGoteHisha },
            { ManagedPieceCode.GoteTokin, ImgGoteTokin },
            { ManagedPieceCode.GoteNariKyo, ImgGoteNariKyo },
            { ManagedPieceCode.GoteNariKei, ImgGoteNariKei },
            { ManagedPieceCode.GoteNariGin, ImgGoteNariGin },
            { ManagedPieceCode.GoteUma, ImgGoteUma },
            { ManagedPieceCode.GoteRyu, ImgGoteRyu },
        };

        public static Image? PieceImage(ManagedPieceCode code)
        {
            return PieceImageMap.GetValueOrDefault(code);
        }
    }
}
