/****************************************************************/
/* File : llips_exemple.c                                       */
/* Description :                                                */
/*   Main functions to demonstrate LLIPS possibility            */
/*                                                              */
/* Author : MPE                                                 */
/*                                                              */
/****************************************************************/

/****************************************************************/
/**           Includes                                          */
/****************************************************************/
#include "includes.h"

/****************************************************************/
/**           Global variables                                  */
/****************************************************************/
CPU_CHAR g_debug_mode = DEF_DISABLED;

/****************************************************************/
/**           Functions                                         */
/****************************************************************/
int main(int argc, char *argv[])
{
    CPU_INT16U i = 1;
    clock_t start, finish;
    double duration;

    t_img img_in1;
    t_img img_in2;
    t_img img_inter1;
    t_img img_inter2;
    t_img img_out1,img_out2;
    CPU_CHAR img_diff_1_2=0;
    t_area change_1_2;

    CPU_CHAR outputfilename[32];

    //CPU_CHAR img_in1_err,img_out1_err;
    //CPU_CHAR contrast_det=0;
    CPU_FP64 ** gauss_filter, **laplace_filter;
    CPU_FP64 gauss_sigma;
    CPU_INT16S gauss_filter_size;
    CPU_INT16S laplace_filter_size;


    /*
    t_img img_in2;
    t_img img_in3;

    t_img img_out2;


    t_vect movement;
    t_vect movement_origin;

    CPU_CHAR img_in1_err,img_in2_err,img_in3_err,img_out1_err,img_out2_err,img_out_move_err;
    CPU_CHAR img_diff_1_2=0,img_diff_2_3=0;

    t_area change_1_2;
    t_area change_2_3;
    */
    start = clock();
    int tolerance, quantity;
    while(i--)
    {


        // checking debug argument
        if (argc == 4)
        {

            if(strcmp(DEBUG_opt, argv[3]) == 0)
            {
                g_debug_mode = DEF_ENABLED;
                printf("%s activated\n",argv[3]);
            }
        }else
        {
            //nothing
        }
        g_debug_mode = DEF_ENABLED;
        if (argc < 3)
        {
            if (g_debug_mode == DEF_ENABLED)
            {
                printf("USAGE: %s <tolerance in percent> <quantity of pixel in perthousand> [opt:DEBUG]\nIncorrect Using default value\n",argv[0]);
            }else
            {
                //nothing
            }

            tolerance = DEFAULT_TOLERANCE;
            quantity = DEFAULT_QUANTITY;

        }else
        {
            sscanf (argv[1],"%d",&tolerance);
            sscanf (argv[2],"%d",&quantity);
            if ((tolerance < 0) || (tolerance > 100))
            {
                printf ("tolerance %d out of bound, using default value : %d\n",tolerance,DEFAULT_TOLERANCE);
                tolerance = DEFAULT_TOLERANCE;
            }
            if ((quantity < 0) || (quantity > 1000))
            {
                printf ("quantity %d out of bound, using default value : %d\n",quantity,DEFAULT_QUANTITY);
                quantity = DEFAULT_QUANTITY ;
            }
        }
        if (g_debug_mode == DEF_ENABLED)
        {
            printf ("tolerance %d\nquantity %d\n",tolerance,quantity);
            printf("Init data\n");
        }else
        {
            //nothing
        }

        init_img(&img_in1);

        load_img((CPU_CHAR *)"imgoutlaplace.bmp", &img_in1);

        apply_median_filter(&img_in1,3,&img_out1);
        sprintf((char *)outputfilename,"%smedian%s",IMG_OUT,BMP_EXT);
        write_img(outputfilename,&img_out1);


/*        init_img(&img_in2);
        init_img(&img_inter1);
        init_img(&img_inter2);
        init_img(&img_out1);
        init_img(&img_out2);

        load_img((CPU_CHAR *)IMG_RIGHT, &img_in1);
        load_img((CPU_CHAR *)IMG_LEFT, &img_in2);

        gauss_sigma = 0.9;
        gauss_filter_size = 3;
        gauss_filter    = createTableFP64(gauss_filter_size,gauss_filter_size);
        create_gauss_filter(gauss_filter,gauss_filter_size,gauss_sigma);
        apply_linfilter(&img_in1,gauss_filter,gauss_filter_size,&img_inter1);

        create_gauss_filter(gauss_filter,gauss_filter_size,gauss_sigma);
        apply_linfilter(&img_in2,gauss_filter,gauss_filter_size,&img_inter2);

//        copy_img(&img_out1,&img_in1);
//        copy_img(&img_out2,&img_in2);

        img_diff_1_2 = search_diff((CPU_CHAR)tolerance,(CPU_CHAR)quantity,&img_inter1,&img_inter2,&img_out1,&change_1_2);
        img_diff_1_2 = search_diff_x((CPU_CHAR)tolerance,(CPU_CHAR)quantity,&img_inter1,&img_inter2,&img_out2,&change_1_2);
        if (img_diff_1_2 == NO_DIFF)
        {
        }else
        {
        }

        //display_img_value(&img_out1,HEADER|BLUE|GREEN|RED|0);
        if((img_diff_1_2 & DIFF_HIGH_QUANTITY)!=0)
        {
            // save a copy
            sprintf((char *)outputfilename,"%sdif%s",IMG_OUT,BMP_EXT);
            write_img(outputfilename,&img_out1);
            sprintf((char *)outputfilename,"%sdif_x%s",IMG_OUT,BMP_EXT);
            write_img(outputfilename,&img_out2);
        }else
        {

            //printf("0\n");
        }


        laplace_filter_size = 3;
        laplace_filter  = createTableFP64(laplace_filter_size,laplace_filter_size);
        create_laplacian_filter(laplace_filter,laplace_filter_size);
        apply_linfilter(&img_in1,gauss_filter,gauss_filter_size,&img_inter1);
        apply_linfilter(&img_inter1,gauss_filter,gauss_filter_size,&img_inter2);
        apply_linfilter(&img_inter2,laplace_filter,laplace_filter_size,&img_out1);
        sprintf((char *)outputfilename,"%sgausslaplace%s",IMG_OUT,BMP_EXT);
        write_img(outputfilename,&img_out1);


        search_contrast((CPU_CHAR)tolerance, &img_in1,&img_out1,SetRGB(255,255,255),(RED|GREEN|BLUE),HOR|VER);
        write_img((CPU_INT08U*)CONTRAST_OUTveho,&img_out1);
*/






/*
        gauss_sigma = 1.2;
        gauss_filter_size = 3;
        gauss_filter    = createTableFP64(gauss_filter_size,gauss_filter_size);
        create_gauss_filter(gauss_filter,gauss_filter_size,gauss_sigma);
        apply_linfilter(&img_in1,gauss_filter,gauss_filter_size,&img_out1);

        laplace_filter_size = 3;
        laplace_filter  = createTableFP64(laplace_filter_size,laplace_filter_size);
        create_laplacian_filter(laplace_filter,laplace_filter_size);
        apply_linfilter(&img_out1,laplace_filter,laplace_filter_size,&img_out2);

        sprintf((char *)outputfilename,"%sgausslaplace%s",IMG_OUT,BMP_EXT);
        write_img(outputfilename,&img_out2);




        laplace_filter_size = 3;
        laplace_filter  = createTableFP64(laplace_filter_size,laplace_filter_size);
        create_laplacian_filter(laplace_filter,laplace_filter_size);
        apply_linfilter(&img_in1,laplace_filter,laplace_filter_size,&img_out1);

        sprintf((char *)outputfilename,"%slaplace%s",IMG_OUT,BMP_EXT);
        write_img(outputfilename,&img_out1);
*/
        /*
        init_img(&img_in2);
        init_img(&img_out2);

        init_img(&img_in3);


        //init_img(&img_out_move);

        img_in1_err = load_img(OLD, &img_in1);
        if (img_in1_err == NO_ERROR)
        {
        }else
        {
            if (g_debug_mode == DEF_ENABLED)
            {
                printf("Image %s not supported - err : %x\n",OLD,img_in1_err);
            }else
            {
                //nothing
            }

        }

        img_in2_err = load_img(BASE, &img_in2);
        if (img_in2_err == NO_ERROR)
        {
        }else
        {
            if (g_debug_mode == DEF_ENABLED)
            {
                printf("Image %s not supported - err : %x\n",BASE,img_in2_err);
            }else
            {
                //nothing
            }

        }

        img_in3_err = load_img(NEW, &img_in3);
        if (img_in3_err == NO_ERROR)
        {
        }else
        {
            if (g_debug_mode == DEF_ENABLED)
            {
                printf("Image %s not supported - err : %x\n",NEW,img_in2_err);
            }else
            {
                //nothing
            }

        }

        if ((img_in1_err == NO_ERROR) && (img_in2_err == NO_ERROR))
        {

            img_diff_1_2 = search_diff((CPU_CHAR)tolerance,(CPU_CHAR)quantity,&img_in1,&img_in2,&img_out1,&change_1_2);
            if (img_diff_1_2 == NO_DIFF)
            {
            }else
            {
            }

            //display_img_value(&img_out1,HEADER|BLUE|GREEN|RED|0);
            if((img_diff_1_2 & DIFF_HIGH_QUANTITY)!=0)
            {
                // save a copy
                img_out1_err = write_img(NEW_DIFF_1,&img_out1);
                if(img_out1_err == NO_ERROR)
                {
                }else
                {
                }
                //printf("1\n");
            }else
            {

                //printf("0\n");
            }


        }else
        {
            //printf("0\n");
        }

        if ((img_in2_err == NO_ERROR) && (img_in3_err == NO_ERROR))
        {

            img_diff_2_3 = search_diff((CPU_CHAR)tolerance,(CPU_CHAR)quantity,&img_in2,&img_in3,&img_out2,&change_2_3);
            if (img_diff_2_3 == NO_DIFF)
            {
            }else
            {
            }

            //display_img_value(&img_out1,HEADER|BLUE|GREEN|RED|0);
            if((img_diff_2_3 & DIFF_HIGH_QUANTITY)!=0)
            {
                // save a copy
                img_out2_err = write_img(NEW_DIFF_2,&img_out2);
                if(img_out2_err == NO_ERROR)
                {
                }else
                {
                }
                //printf("1\n");
            }else
            {

                //printf("0\n");
            }


        }else
        {
            //printf("0\n");
        }

        // Determine mouvement
        if(((img_diff_1_2 & DIFF_HIGH_QUANTITY)!=0) && ((img_diff_2_3 & DIFF_HIGH_QUANTITY)!=0))
        {
            init_img(&img_out2);
            //evaluate_move(&img_in2,&img_out_move,change_1_2,change_2_3);
            //img_out_move_err = write_img(MOVE,&img_out_move);
            movement = evaluate_move(&img_in2,&img_out2,change_1_2,change_2_3,&movement_origin);
            img_out_move_err = write_img(MOVE,&img_out2);
            if(img_out_move_err == NO_ERROR)
            {
                //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
            }else
            {
                printf("0\t0\t0\n");
            }

        }else
        {
            printf("0\t0\t0\n");
        }


*/    }

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
    /* color filtering on BASE */
/*
    init_img(&img_in1);
    img_in1_err = load_img(BASE, &img_in1);
    if (img_in1_err == NO_ERROR)
    {
    }else
    {
        if (g_debug_mode == DEF_ENABLED)
        {
            printf("Image %s not supported - err : %x\n",BASE,img_in1_err);
        }else
        {
            //nothing
        }

    }

    init_img(&img_out1);
    color_filter(&img_in1,&img_out1, (RED));
    img_out1_err = write_img(IMG_RED,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }


*/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
    /* Contrast Detection on BASE */
 /*
    init_img(&img_in1);
    img_in1_err = load_img((CPU_CHAR *)BASE, &img_in1);
    if (img_in1_err == NO_ERROR)
    {
    }else
    {
        if (g_debug_mode == DEF_ENABLED)
        {
            printf("Image %s not supported - err : %x\n",BASE,img_in1_err);
        }else
        {
            //nothing
        }

    }

    tolerance = 7;

    init_img(&img_out1);
    search_contrast((CPU_CHAR)tolerance, &img_in1,&img_out1,SetRGB(255,255,255),(RED|GREEN|BLUE),VER);
    img_out1_err = write_img((CPU_CHAR *)CONTRAST_OUTVRT,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }

    init_img(&img_out1);
    search_contrast((CPU_CHAR)tolerance, &img_in1,&img_out1,SetRGB(255,255,255),(RED|GREEN|BLUE),HOR);
    img_out1_err = write_img((CPU_CHAR *)CONTRAST_OUTHRZ,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }

    init_img(&img_out1);
    search_contrast((CPU_CHAR)tolerance, &img_in1,&img_out1,SetRGB(255,255,255),(RED|GREEN|BLUE),HOR|VER);
    img_out1_err = write_img(CONTRAST_OUTveho,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }*/


/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
    /* histogram calculation on BASE
    init_img(&img_in1);
    img_in1_err = load_img(BASE, &img_in1);
    if (img_in1_err == NO_ERROR)
    {
    }else
    {
        if (g_debug_mode == DEF_ENABLED)
        {
            printf("Image %s not supported - err : %x\n",BASE,img_in1_err);
        }else
        {
            //nothing
        }

    }




    init_img(&img_out1);
    histogram(&img_in1,&img_out1);
    img_out1_err = write_img(IMG_HISTO,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }*/

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
    /* luminance on BASE */
    /*init_img(&img_in1);
    img_in1_err = load_img(BASE, &img_in1);
    if (img_in1_err == NO_ERROR)
    {
    }else
    {
        if (g_debug_mode == DEF_ENABLED)
        {
            printf("Image %s not supported - err : %x\n",BASE,img_in1_err);
        }else
        {
            //nothing
        }

    }

    init_img(&img_out1);
    luminance(&img_out1,&img_out1);
    img_out1_err = write_img((CPU_CHAR *)IMG_LUM,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }*/

/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
    /* smooth filter on BASE */
/*
    init_img(&img_in1);
    img_in1_err = load_img((CPU_CHAR *)BASE, &img_in1);
    if (img_in1_err == NO_ERROR)
    {
    }else
    {
        if (g_debug_mode == DEF_ENABLED)
        {
            printf("Image %s not supported - err : %x\n",BASE,img_in1_err);
        }else
        {
            //nothing
        }

    }
    sigma = 1.1;
    filtresize = 3;
//Gaussian filter

    sprintf((char *)outputfilename,"%sGsig%0.1ffsize%02d%s",IMG_SMOOTH,sigma,filtresize,BMP_EXT);

    init_img(&img_out1);
    filtre = createTableFP64(filtresize,filtresize);
    create_gauss_filter(filtre,filtresize,sigma);
    apply_linfilter(&img_in1,filtre,filtresize,&img_out1);

    img_out1_err = write_img((CPU_CHAR *)outputfilename,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }
*/
//Median filter
/*
    sprintf((char *)outputfilename,"%sMfsize%02d%s",IMG_SMOOTH,filtresize,BMP_EXT);

    init_img(&img_out1);
    filtre = createTableFP64(filtresize,filtresize);
    create_average_filter(filtre,filtresize);
    apply_linfilter(&img_in1,filtre,filtresize,&img_out1);

    img_out1_err = write_img((CPU_CHAR *)outputfilename,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }
*/
//gaussian filter x10
/*

    filtre = createTableFP64(filtresize,filtresize);
    create_gauss_filter(filtre,filtresize,sigma);
    for(i=0;i<0;i++)
    {
        apply_linfilter(&img_in1,filtre,filtresize,&img_out1);
        copy_img(&img_out1,&img_in1);
    }



    sprintf((char *)outputfilename,"%sM10fsize%02d%s",IMG_SMOOTH,filtresize,BMP_EXT);
    img_out1_err = write_img((CPU_CHAR *)outputfilename,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }
*/

//Laplacian filter
/*
    filtre = createTableFP64(filtresize,filtresize);
    filtresize = create_laplacian_filter(filtre);

    apply_linfilter(&img_in1,filtre,filtresize,&img_out1);

    sprintf((char *)outputfilename,"%ssize%02d%s","imgcontourlaplace",filtresize,BMP_EXT);
    img_out1_err = write_img((CPU_CHAR *)outputfilename,&img_out1);
    if(img_out1_err == NO_ERROR)
    {
        //printf("1\t%d\t%d\n",movement.x,movement_origin.x);
    }else
    {
        printf("write error\n");
    }
*/




/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
/*********************************************************************************/
    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf( "duration : %f seconds\n", duration );

    return 0;
}

