#include "cekla.h"

// revapp(L, L0) = az L lista megfordítása L0 elé fuzve
list revapp(const list L, const list L0)
{
  if (L == nil) return L0;
  return revapp(tl(L), cons(hd(L), L0));
}

// reverse(L) = az L lista megfordítva
list reverse(const list L) {
  return revapp(L, nil);
}

// convert10toX(D,X) = a D decimalis szam felbontva X szamrendszerbe es szamjegyenkent listaban abrazolva
list convert10toX(const int D, const int X){
    const int TMP = D/X;
    if(TMP == 0)
        return cons(D%X, nil);
    else
        return cons(D%X,convert10toX(TMP, X));
}

// convert(L,D,X) = az L listaban szamjegyenkent X szamrendszerben abrazolt szam visszaalakiitasa decimalis formaba
int convert(const list L, const int D, const int X){
    if(L==nil) return 0;
    return hd(L)*D + convert(tl(L),D*X,X);
}

// convertXto10(L,X) = convert fuggveny D argumentumanak elfedese
int convertXto10(const list L, const int X){
    return convert(L,1,X);
}

// listLength(L) = visszaadja az L lista hosszat
int listLength(const list L){
    if(L == nil)
        return 0;
    return 1+listLength(tl(L));
}

// collect(L,D) = visszaadja az L lista paros, vagy paratlan indexu elemeit egy listaban.
//	D==0 akkor paratan,
//	D==1 akkor paros elemeket.
list collect(const list L, const int D){
    if(L == nil)
        return nil;
    if(D%2 == 0)
        return cons(hd(L),collect(tl(L),D+1));
    else
        return collect(tl(L),D+1);
}

// collectPair(L) = visszaadja az L lista paros indexu elemeit
list collectPair(const list L){
    return collect(L,0);
}

// collectPair(L) = visszaadja az L lista paratan indexu elemeit
list collectImpair(const list L){
    return collect(L,1);
}

// mergePair(LP,LIP) = listakent visszaadja az LP es LIP listak osszefuzott valtozatat, hogy a paros es paratlan indexek a helyiukre keruljenek
// azonos mennyisegu paros es paratlan indexu elem van
list mergePair(const list LP, const list LIP){
    if(LP == nil)
        return nil;
    return cons(hd(LP),cons(hd(LIP), mergePair(tl(LP),tl(LIP))));
}

// mergeImpair(LP,LIP) = listakent visszaadja az LP es LIP listak osszefuzott valtozatat, hogy a paros es paratlan indexek a helyiukre keruljenek
// tobb paratlan indexu elem van mint paros
list mergeImpair(const list LP, const list LIP){
    if(LP == nil)
        return cons(hd(LIP),nil);
    return cons(hd(LIP),cons(hd(LP), mergeImpair(tl(LP),tl(LIP))));
}

/* osszekevert(S, A) == SK, ha SK az S szám A alapú összekevert
   változata (S>0, A>1 egész számok).
   Egy S szám A alapú összekevertjét úgy kapjuk meg, hogy az S számot felírjuk
   az A alapú számrendszerben, a számjegyeit egy listával ábrázoljuk, a
   listát a fentiek szerint átrendezzük, majd a kapott lista elemeit
   egy A alapú szám jegyeinek tekintve elõállítjuk a keresett értéket.
*/
int osszekevert(const int S, const int A) {
    const list L0 = convert10toX(S,A);			//beolvassuk az S decimalis szamot A szemrendszerkent az L0 lisaba szamjegyenkent
    const int D0 = listLength(L0);				//megnezzuk a lista hosszat, hogy milyen muveletet vegezzunk kesobb
	
    if(D0%2 == 0)
    {
		/* L0 listabol kivalogatjuk a paros es paratlan indexu elemeket. A parosokat tartalmazo listat megforgatjuk es 
		   a ket listat osszefesuljuk, de mivel megdordult a sorrend ezert meg ezt is megforgatjuk, hogy a decimalis formaban torteno
		   visszaalakiitashoz, ne kelljen az L0 lista hosszat hasznalni. Vegul visszaalakitjuk decimalis formara.
		*/
        return convertXto10(reverse(mergePair(reverse(collectImpair(L0)),collectPair(L0))),A);
    }
    else
    {
        return convertXto10(reverse(mergeImpair(collectImpair(L0),reverse((collectPair(L0))))),A);
    }
}
