#include"Adaboost.h"
#include"HaarFeatures.h"
#include"Sort.h"
#include"Training.h"

double sumWeight(struct WeakClassifier *wc,int size)
{
  double res = 0.0;
  for(int i = 0;i<size;i++)
    res += wc[i].w;
  return res;

}

void Boost(struct StrongClassifier *sc,struct ImgVal *img, int nbImg, int pos)
{
  int t = 0;
  double e = 2;
  struct HaarFeat* haar = malloc(sizeof(struct HaarFeat));
  int T = 5;
  /* initialisation of weights */
  for(int i = 0;i<pos;i++)
  {
    img->wc[i].w = 1/(2*pos);
    img->wc[i].polarity = 1;
  }

  for(int i = pos;i<nbImg;i++)
  {
    img->wc[i].w = 1/(2*(nbImg-pos));
    img->wc[i].polarity = -1;                
  }



  /* main loop */
  for(;t<T;t++)
  {
    printf("start");
    for(int i = 0;i<nbImg;i++)
    {
      img->wc[i].w /= sumWeight(img->wc,nbImg);
    }
    printf("end");

    /* select the best weak classifier */
    for(int feat = 1;feat<=5;feat++)
    {
      printf("%d",feat);
      haar->x = 0;
      haar->y = 0;
      haar->w = 0;
      haar->h = 0;

      if(feat ==1)
      {
        haar->feat = 1;
        for(haar->x = 0; haar->x<19; haar->x++)
        {
          for(haar->y = 0; haar->y<19; haar->y++)
          {
            for(haar->h = 1; haar->x+haar->h<19; haar->h++)
            {
              for(haar->w = 1;haar->y+2*haar->w<19; haar->w++)
              {
                for(int i = 0;i<nbImg;i++)
                {
                  ValFeatA(haar,img->wc[i].integ);
                  img->wc[i].feature = haar;
                }
                selectBestFeat(img,nbImg);
                if(img->e<e)
                {
                  e = img->e;
                  for(int i = 0;i<nbImg;i++)
                  {
                    img->wc[i].threshold = img->theta;
                  }
                  
                  sc->wc[t].feature = haar;
                  printf("%d %d %d %d %d\n",haar->x,haar->y,haar->w,haar->h,haar->feat);
                  sc->wc[t].threshold = img->theta;
                  sc->wc[t].polarity = img->T;
                }
              }
            }
          }
        }
      }
      else if(feat == 2)
      {
        haar->feat = 2;
        for(haar->x = 0; haar->x<19; haar->x++)
        {
          for(haar->y = 0; haar->y<19; haar->y++)
          {
            for(haar->h = 1; haar->x+haar->h<19; haar->h++)
            {
              for(haar->w = 1;haar->y+3*haar->w<19; haar->w++)
              {
                for(int i = 0;i<nbImg;i++)
                {
                  ValFeatB(haar,img->wc[i].integ);
                  img->wc[i].feature = haar;
                }
                selectBestFeat(img,nbImg);
                if(img->e<e)
                {
                  e = img->e;
                  for(int i = 0;i<nbImg;i++)
                  {
                    img->wc[i].threshold = img->theta;
                  }
                  
                  sc->wc[t].feature = img->wc[0].feature;
                  sc->wc[t].threshold = img->theta;
                  sc->wc[t].polarity = img->T;
                }
              }
            }
          }
        }

      }
      else if(feat == 3)
      {
        haar->feat = 3;
        for(haar->x = 0; haar->x<19; haar->x++)
        {
          for(haar->y = 0; haar->y<19; haar->y++)
          {
            for(haar->h = 1; haar->x+2*haar->h<19; haar->h++)
            {
              for(haar->w = 1; haar->y+haar->w<19; haar->w++)
              {
                for(int i = 0;i<nbImg;i++)
                {
                  ValFeatC(haar,img->wc[i].integ);
                  img->wc[i].feature = haar;
                }
                selectBestFeat(img,nbImg);
                if(img->e<e)
                {
                  e = img->e;
                  for(int i = 0;i<nbImg;i++)
                  {
                    img->wc[i].threshold = img->theta;
                  }
                  
                  sc->wc[t].feature = img->wc[0].feature;
                  sc->wc[t].threshold = img->theta;
                  sc->wc[t].polarity = img->T;
                }
              }
            }
          }
        }

      }
      else if(feat == 4)
      {
        haar->feat = 4;
        for(haar->x = 0; haar->x<19; haar->x++)
        {
          for(haar->y = 0; haar->y<19; haar->y++)
          {
            for(haar->h = 1; haar->x+3*haar->h<19; haar->h++)
            {
              for(haar->w = 1; haar->y+haar->w<19; haar->w++)
              {
                for(int i = 0;i<nbImg;i++)
                {
                  ValFeatD(haar,img->wc[i].integ);
                  img->wc[i].feature = haar;
                }
                selectBestFeat(img,nbImg);
                if(img->e<e)
                {
                  e = img->e;
                  for(int i = 0;i<nbImg;i++)
                  {
                    img->wc[i].threshold = img->theta;
                  }
                  
                   sc->wc[t].feature = img->wc[0].feature;
                   sc->wc[t].threshold = img->theta;
                   sc->wc[t].polarity = img->T;
                }
              }
            }
          }
        }

      }
      else if(feat == 5)
      {
        haar->feat = 5;
        for(haar->x = 0; haar->x<19; haar->x++)
        {
          for(haar->y = 0; haar->y<19; haar->y++)
          {
            for(haar->h = 1; haar->x+2*haar->h<19; haar->h++)
            {
              for(haar->w = 1;haar->y+2*haar->w<19; haar->w++)
              {
                for(int i = 0;i<nbImg;i++)
                {
                  ValFeatE(haar,img->wc[i].integ);
                  img->wc[i].feature = haar;
                }
                selectBestFeat(img,nbImg);
                if(img->e<e)
                {
                  e = img->e;
                  for(int i = 0;i<nbImg;i++)
                  {
                    img->wc[i].threshold = img->theta;
                  }
                  
                   sc->wc[t].feature = img->wc[0].feature;
                   sc->wc[t].threshold = img->theta;
                   sc->wc[t].polarity = img->T;
                }
              }
            }
          }
        }

      }

    }
    sc->alpha[t] = alpha_calcul(e);
    update_weight(e,img,t);
    printf("%d",t);


  }  
  free(haar);
  save_training(sc,5);
}


double alpha_calcul(double epsError) {
  return log((1-epsError)/epsError);
}

/* Deleted 
// Don't know if it's better to replace by WeakClassifier wc
void add_wc(struct StrongClassifier* sc, struct HaarFeat* feat, int threshold, int pol, int sw[19][19], int epsError, int round) {
  struct WeakClassifier weak;
  weak.feature 		= feat;
  weak.threshold = threshold;
  weak.polarity 	= pol;
  for(int i =0;i<19;i++)
  {
    for(int j = 0;j<19;j++)
      weak.integ[i][j]			= sw[i][j];
  }

  sc->wc[round] 	= weak;

  // calcul alpha
  sc->alpha[round] = alpha_calcul(epsError);
}
*/
int wc_calcul(struct WeakClassifier* wc) {
  return (wc->feature->val * wc->polarity < wc->threshold * wc->polarity) ? 1 : 0;  
}

void update_weight(double epsError, struct ImgVal* img, int round) {
  if(round < 5) {
    double beta = epsError / (1 - epsError);
    int ei = 0;
    for(int i = 1; i < 6400; i++) { 
      if(wc_calcul(&(img->wc[i])) * img->wc[i].polarity * -alpha_calcul(epsError) > 0)
        ei = 1;
      else
        ei = 0;

      img->wc[i].w *= pow(beta, 1-ei);
    } 

  }
}


// C(X) where X is an image. 
// TODO : final_sc(SDL_Surface* img, StrongClassifier* sc) ??
int	final_sc(struct StrongClassifier* sc) {
  double sumSC = 0, sumAlpha = 0;
  for(int i = 0; i < 5; i++) {
    sumSC += sc->alpha[i] * wc_calcul(&(sc->wc[i]));
    sumAlpha += sc->alpha[i] * 0.5;
  }

  return (sumSC >= sumAlpha) ? 1 : 0;
}


void selectBestFeat(struct ImgVal *img,int nbImg)
{
  //    sorted img + weights
  sort(img);
  double Sp = 0,Sn = 0, Tp = 0, Tn = 0;
  int Te = 0;
  int t = img->wc[0].feature->val;
  int M = 0;
  double e = 2;

  for(int i = 0;i<nbImg;i++)
  {
    if(img->wc[i].polarity == 1)
      Tp += img->wc[i].w;
    else
      Tn += img->wc[i].w;
  }
  int jIter = 0;
  int tIter = t;
  int MIter = M;
  int TIter;
  double eIter;
  double Ep,En;
  while(1){
    Ep = Sp+Tn;
    En = Tp+Sn;
    if(Ep<En)
    {
      eIter = Ep;
      TIter = 1;
    }
    else
    {
      eIter = En;
      TIter = -1;
    }
    if(eIter<=e && MIter>M)
    {
      e = eIter;
      t = tIter;
      M = MIter;
      Te = TIter;
    }
    if(jIter == nbImg-1)
      break;
    jIter++;
    while(1){
      if(img->wc[jIter].polarity == -1)
      {
        Sn += img->wc[jIter].w;
        Tn -= img->wc[jIter].w;
      }
      else
      {
        Sp += img->wc[jIter].w;
        Tp -= img->wc[jIter].w;
      }
      if(jIter == nbImg-1 || img->wc[jIter].feature->val)
        break;
      else
        jIter++;
    }
    if(jIter == nbImg-1)
    {
      tIter = img->wc[jIter].feature->val + 1;
      MIter = 0;
    }
    else
    {
      tIter=(img->wc[jIter].feature->val+img->wc[jIter+1].feature->val)/2;
      MIter = img->wc[jIter+1].feature->val -img->wc[jIter].feature->val;
    }
  }
  img->theta = t;
  img->e=e;
  img->M=M;
  img->T=Te;

}
